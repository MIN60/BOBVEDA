#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "struct.h"
#include "randomize.h"
//각 팀에 이전팀과 성비를 고려하여 조를 짜는 함수
// TeamSelect 함수 수정
int TeamSelect(TEAM* Team, MEMBER* Male, MEMBER* Female, int Mcount, int Fcount, int team_count) {
    int* FemaleIdx = CreateNumArr(Fcount);
    int* MaleIdx = CreateNumArr(Mcount);
    int LastIndex = team_count - 1; // 마지막 팀 인덱스
    int idx = 0; // 현재 조
    int RemainingF = Fcount; // 남은 여성 인원 수
    int RemainingM = Mcount; // 남은 남성 인원 수
    int SelectedIdx; // 선택된 번호(자리)
    int wcount = 0;
    int mcount = 0;
    for (int i = 0; i < team_count; i++) // 각 팀 인원 0으로 초기화
    {
        Team[i].count = 0;
    }
    // 여성 추가 - 먼저 여성을 각 팀에 최대한 균등하게 배분
    for (int i = 0; i < Fcount;) {
        // 안전장치: 너무 많은 시도 후에도 배정 못하면 중복 체크 무시하고 진행
        int attempts = 0;
        int maxAttempts = 50; // 최대 시도 횟수 제한
        while (attempts < maxAttempts) {
            int Random_Idx = RandomNumber(RemainingF); // 랜덤 Idx 지정
            SelectedIdx = FemaleIdx[Random_Idx]; // 남은 사람 중 뽑음
            int teamIdx = idx % team_count; // 팀 인덱스를 순환하도록 수정
            if (!DuplCheck(Female[SelectedIdx].prev_team, Team[teamIdx].set)) {
                // 중복 없음 - 배정 진행
                wcount++;
                Team[teamIdx].member[(Team[teamIdx].count)] = Female[SelectedIdx]; // 멤버 삽입, 멤버 수 증가
                Team[teamIdx].set[Team[teamIdx].count] = Female[SelectedIdx].prev_team; // 현재 조 set을 업데이트
                Team[teamIdx].count++;
                ArrUpdate(&FemaleIdx, &RemainingF, Random_Idx); // 배열 감소
                idx++; // 다음조로 이동
                i++;
                break; // 성공했으니 내부 while 루프 탈출
            }
            attempts++;
            // 안전장치: 너무 많은 시도 후에도 배정 못하면 중복 무시하고 진행
            if (attempts >= maxAttempts) {
                //printf("여성 배정 실패 후 중복 무시하고 진행: %s\n", Female[SelectedIdx].name);
                Team[teamIdx].member[(Team[teamIdx].count)] = Female[SelectedIdx];
                Team[teamIdx].set[Team[teamIdx].count] = Female[SelectedIdx].prev_team;
                Team[teamIdx].count++;
                ArrUpdate(&FemaleIdx, &RemainingF, Random_Idx);
                idx++;
                i++;
                break;
            }
        }
    }
    // 남성 추가 - 여성과 동일한 방식으로 안전장치 추가
    for (int i = 0; i < Mcount;) {
        int attempts = 0;
        int maxAttempts = 50; // 최대 시도 횟수 제한
        while (attempts < maxAttempts) {
            int Random_Idx = RandomNumber(RemainingM); // 랜덤 Idx 지정
            SelectedIdx = MaleIdx[Random_Idx]; // 남은 사람 중 뽑음
            int teamIdx = idx % team_count; // 팀 인덱스를 순환하도록 수정
            if (!DuplCheck(Male[SelectedIdx].prev_team, Team[teamIdx].set)) {
                // 중복 없음 - 배정 진행
                mcount++;
                Team[teamIdx].member[(Team[teamIdx].count)] = Male[SelectedIdx]; // 멤버 삽입, 멤버 수 증가
                Team[teamIdx].set[Team[teamIdx].count] = Male[SelectedIdx].prev_team; // 현재 조 set을 업데이트
                Team[teamIdx].count++;
                ArrUpdate(&MaleIdx, &RemainingM, Random_Idx); // 배열 감소
                idx++; // 다음조로 이동
                i++;
                break; // 성공했으니 내부 while 루프 탈출
            }
            attempts++;
            // 안전장치: 너무 많은 시도 후에도 배정 못하면 중복 무시하고 진행
            if (attempts >= maxAttempts) {
                //printf("남성 배정 실패 후 중복 무시하고 진행: %s\n", Male[SelectedIdx].name);
                Team[teamIdx].member[(Team[teamIdx].count)] = Male[SelectedIdx];
                Team[teamIdx].set[Team[teamIdx].count] = Male[SelectedIdx].prev_team;
                Team[teamIdx].count++;
                ArrUpdate(&MaleIdx, &RemainingM, Random_Idx);
                idx++;
                i++;
                break;
            }
        }
    }
    free(FemaleIdx);
    free(MaleIdx);
    return 0; // 정상 종료
}
// 중복을 검사하는 함수
int DuplCheck(int n, int* arr) // 중복됨: 1(true), 중복되지않음: 0(false)
{
    if (n == -1) return 0; // 이전 팀이 없는 경우 중복 체크 안 함
    else
    {
        for (int i = 0; i < 5; i++) // 최대 5명까지 체크
        {
            if (arr[i] == n)
            {
                return 1; // 중복 발견
            }
        }
        return 0; // 중복 없음
    }
}
void InitRandom() {
    srand(time(NULL)); // 프로그램 시작 시 한 번만 실행
}
// 0 ~ num-1의 난수 출력
int RandomNumber(int num) {
    if (num <= 0) return -1; // 안전 장치
    return rand() % num;
}
// 숫자 구성 배열 생성
int* CreateNumArr(int num) {
    int* new_arr = malloc(sizeof(int) * num);
    for (int i = 0; i < num; i++) {
        new_arr[i] = i;
    }
    return new_arr;
}
// 전체인원을 성별에 따라 분류하는 함수
void Classification(MEMBER* Tptr, MEMBER* Mptr, MEMBER* Fptr, MEMBER* temp, const int size, int* FCount, int* MCount, int* TCount)
{
    *FCount = 0; // 여성 수
    *MCount = 0; // 남성 수
    *TCount = 0; // 이외 인원 수
    for (int i = 0; i < size; i++)
    {
        if (Tptr[i].gender == 'F')
        {
            Fptr[*FCount] = Tptr[i];
            ++(*FCount);
        }
        else if (Tptr[i].gender == 'M')
        {
            Mptr[*MCount] = Tptr[i];
            ++(*MCount);
        }
        else if (Tptr[i].gender == 'N' || Tptr[i].gender == 'E')
        {
            temp[*TCount] = Tptr[i];
            ++(*TCount);
        }
    }
}
void ArrUpdate(int** arr, int* size, int index) {
    if (*size <= 0 || index >= *size) return;
    // 선택된 인덱스의 값과 마지막 값을 교환
    int temp = (*arr)[index];
    (*arr)[index] = (*arr)[*size - 1];
    (*arr)[*size - 1] = temp;
    // 크기 감소
    (*size)--;
    // 배열의 크기를 줄임
    if (*size > 0) {
        int* temp_arr = realloc(*arr, (*size) * sizeof(int));
        if (temp_arr == NULL) {
            perror("Memory reallocation failed");
            exit(1);
        }
        *arr = temp_arr;
    }
    else {
        free(*arr);
        *arr = NULL;
    }
}
// 남성과 여성 배열을 출력하는 함수
void PrintMembers(MEMBER* Male, MEMBER* Female, MEMBER* Temp, int Mcount, int Fcount, int Tcount) {
    printf("남성 멤버:\n");
    for (int i = 0; i < Mcount; i++) {
        printf("%s %d %c\n", Male[i].name, Male[i].prev_team, Male[i].gender);
    }
    printf("\n여성 멤버:\n");
    for (int i = 0; i < Fcount; i++) {
        printf("%s %d %c\n", Female[i].name, Female[i].prev_team, Female[i].gender);
    }
    printf("\n제외 인원:\n");
    for (int i = 0; i < Tcount; i++) {
        printf("%s %d %c\n", Temp[i].name, Temp[i].prev_team, Temp[i].gender);
    }
}