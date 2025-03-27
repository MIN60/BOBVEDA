#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

typedef struct MEMBER MEMBER;
typedef struct TEAM TEAM;

void ReadOrigin(MEMBER* members, const char* file_name);
void printOrigin(MEMBER* members, int count);
void PrintMembers(MEMBER* Male, int Mcount, MEMBER* Female, int Fcount);
void WriteText(TEAM* teams, MEMBER* Temp, int ab_num, int team_count, const char* file_name);

void InitRandom();
int RandomNumber(int num);

int Absent(MEMBER* member, char* ab_name);
void Classification(MEMBER* Tptr, MEMBER* Mptr, MEMBER* Fptr, MEMBER* temp, const int size, int* FCount, int* MCount, int* TCount);
int* CreateNumArr(int num);
int TeamSelect(TEAM* Team, MEMBER* Male, MEMBER* Female, int Mcount, int Fcount);
int DuplCheck(int n, int* arr);
void ArrUpdate(int** arr, int* size, int index);
void Genderchange(MEMBER* Temp, int size);


struct MEMBER {
    char name[20];
    int prev_team; // 직전 조가 없었던 경우 -1로 초기화
    char gender; // f:female, m:male
};

struct TEAM {
    MEMBER* member; //member 추가할 배열
    int set[5]; //중복 checking할 배열 -1로 초기화
    int count; //멤버 수, TeamSelect함수 내에서 0으로 초기화
};


int main(int argc, char* argv[]) {
    if (argc < 4) {
        printf("누락: ./group_maker input.txt excludeList output.txt\n");
        return 1;
    }

    const char* input_file = argv[1];
    const char* exclude_list = argv[2];
    const char* output_file = argv[3];

    MEMBER member[30]; // 전체 멤버
    MEMBER absent[30]; // 제외된 멤버
    MEMBER Male[30], Female[30], Temp[30]; // 성별 분류
    int Mcount, Fcount, Tcount;

    // 입력 파일 읽기
    ReadOrigin(member, input_file);

    // 제외자 처리
    char ab_copy[256];
    strncpy(ab_copy, exclude_list, sizeof(ab_copy));
    ab_copy[sizeof(ab_copy) - 1] = '\0';
    int ab_num = Absent(member, ab_copy);

    // 성별 분류
    Classification(member, Male, Female, Temp, 30, &Fcount, &Mcount, &Tcount);

    // 결석자 성별 변환
    Genderchange(Temp, ab_num);

    // 팀 생성
    TEAM teams[7];
    for (int i = 0; i < 7; i++) {
        teams[i].member = (MEMBER*)malloc(sizeof(MEMBER) * 5);
        if (!teams[i].member) {
            perror("Memory allocation failed");
            exit(1);
        }
        for (int j = 0; j < 5; j++) {
            teams[i].set[j] = -1;
        }
    }

    // 팀 배정
    InitRandom();
    TeamSelect(teams, Male, Female, Mcount, Fcount);

    // 결과 파일 저장
    WriteText(teams, Temp, ab_num, 7, output_file);

    // 메모리 해제
    for (int i = 0; i < 7; i++) {
        free(teams[i].member);
    }

    return 0;
}

//각 팀에 이전팀과 성비를 감안하여 조를 짜는 함수
//int TeamSelect(TEAM* Team, MEMBER* Male, MEMBER* Female, int Mcount, int Fcount) {
//
//    printf("select\n");
//    int* FemaleIdx = CreateNumArr(Fcount);
//    int* MaleIdx = CreateNumArr(Mcount);
//
//    int LastIndex = 6;//끝 조 인덱스
//    int idx = 0;//현재 조
//
//    int RemainingF = Fcount;//남은 여성 인원 수
//    int RemainingM = Mcount;//남은 남성 인원 수
//
//    int SelectedIdx;//선택된 번호(자리)
//    int cnt = 0; //무한 루프 확인
//
//
//    int wcount = 0;
//    int mcount = 0;
//
//
//    for (int i = 0; i < 7; i++)//각 팀 인원 0으로 초기화
//    {
//        Team[idx+i].count = 0;
//    }
//
//    //여성 추첨
//    for (int i = 0; i < Fcount;) {
//        int Random_Idx = RandomNumber(RemainingF);//랜덤 Idx 지정
//        SelectedIdx = FemaleIdx[Random_Idx]; //남은 사람 중 뽑음
//        int teamIdx = idx % (LastIndex + 1);
//
//        if (DuplCheck(Female[SelectedIdx].prev_team, Team[teamIdx].set)) {//중복 팀 확인
//            continue; //재추첨
//        }
//        else
//        {
//            printf("여성 선정 횟수 %d\n", wcount++);
//            Team[teamIdx].member[(Team[teamIdx].count)] = Female[SelectedIdx];//멤버 삽입, 멤버 수 증가
//            Team[teamIdx].set[Team[teamIdx].count] = Female[SelectedIdx].prev_team; //현재 조 set을 업데이트
//            Team[teamIdx].count++;
//            ArrUpdate(&FemaleIdx, &RemainingF, Random_Idx); //배열 축소
//            idx++; //다음조로 이동
//            i++;
//        }
//    }
//
//    //남성 추첨
//    for (int i = 0; i < Mcount;) {
//        int Random_Idx = RandomNumber(RemainingM);//랜덤 Idx 지정
//        SelectedIdx = MaleIdx[Random_Idx]; //남은 사람 중 뽑음
//        int teamIdx = idx % (LastIndex + 1);
//        if (DuplCheck(Male[SelectedIdx].prev_team, Team[teamIdx].set)) {//중복 팀 확인
//            continue;//재추첨
//        }
//        else
//        {
//            printf("남성 선정 횟수 %d\n", mcount++);
//            Team[teamIdx].member[(Team[teamIdx].count)] = Male[SelectedIdx];//멤버 삽입, 멤버 수 증가
//            Team[teamIdx].set[Team[teamIdx].count] = Male[SelectedIdx].prev_team; //현재 조 set을 업데이트
//            Team[teamIdx].count++;
//            ArrUpdate(&MaleIdx, &RemainingM, Random_Idx); //배열 축소
//            idx++; //다음조로 이동
//            i++;
//        }
//    }
//
//   
//
//    free(FemaleIdx);
//    free(MaleIdx);
//}
// TeamSelect 함수 수정
int TeamSelect(TEAM* Team, MEMBER* Male, MEMBER* Female, int Mcount, int Fcount) {
    printf("select\n");
    int* FemaleIdx = CreateNumArr(Fcount);
    int* MaleIdx = CreateNumArr(Mcount);

    int LastIndex = 6;//끝 조 인덱스
    int idx = 0;//현재 조

    int RemainingF = Fcount;//남은 여성 인원 수
    int RemainingM = Mcount;//남은 남성 인원 수

    int SelectedIdx;//선택된 번호(자리)
    int wcount = 0;
    int mcount = 0;

    for (int i = 0; i < 7; i++)//각 팀 인원 0으로 초기화
    {
        Team[i].count = 0;
    }

    //여성 추첨
    for (int i = 0; i < Fcount;) {
        // 안전장치: 너무 많은 시도 후에도 배정 못하면 중복 체크 무시하고 진행
        int attempts = 0;
        int maxAttempts = 50; // 최대 시도 횟수 제한

        while (attempts < maxAttempts) {
            int Random_Idx = RandomNumber(RemainingF);//랜덤 Idx 지정
            SelectedIdx = FemaleIdx[Random_Idx]; //남은 사람 중 뽑음
            int teamIdx = idx % (LastIndex + 1);

            if (!DuplCheck(Female[SelectedIdx].prev_team, Team[teamIdx].set)) {
                // 중복 없음 - 배정 진행
                printf("여성 선정 횟수 %d\n", wcount++);
                Team[teamIdx].member[(Team[teamIdx].count)] = Female[SelectedIdx];//멤버 삽입, 멤버 수 증가
                Team[teamIdx].set[Team[teamIdx].count] = Female[SelectedIdx].prev_team; //현재 조 set을 업데이트
                Team[teamIdx].count++;
                ArrUpdate(&FemaleIdx, &RemainingF, Random_Idx); //배열 축소
                idx++; //다음조로 이동
                i++;
                break; // 성공했으니 내부 while 루프 탈출
            }

            attempts++;
            // 안전장치: 너무 많은 시도 후에도 배정 못하면 중복 무시하고 진행
            if (attempts >= maxAttempts) {
                printf("여성 배정 실패 후 중복 무시하고 진행: %s\n", Female[SelectedIdx].name);
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

    //남성 추첨 - 여성과 동일한 방식으로 안전장치 추가
    for (int i = 0; i < Mcount;) {
        int attempts = 0;
        int maxAttempts = 50; // 최대 시도 횟수 제한

        while (attempts < maxAttempts) {
            int Random_Idx = RandomNumber(RemainingM);//랜덤 Idx 지정
            SelectedIdx = MaleIdx[Random_Idx]; //남은 사람 중 뽑음
            int teamIdx = idx % (LastIndex + 1);

            if (!DuplCheck(Male[SelectedIdx].prev_team, Team[teamIdx].set)) {
                // 중복 없음 - 배정 진행
                printf("남성 선정 횟수 %d\n", mcount++);
                Team[teamIdx].member[(Team[teamIdx].count)] = Male[SelectedIdx];//멤버 삽입, 멤버 수 증가
                Team[teamIdx].set[Team[teamIdx].count] = Male[SelectedIdx].prev_team; //현재 조 set을 업데이트
                Team[teamIdx].count++;
                ArrUpdate(&MaleIdx, &RemainingM, Random_Idx); //배열 축소
                idx++; //다음조로 이동
                i++;
                break; // 성공했으니 내부 while 루프 탈출
            }

            attempts++;
            // 안전장치: 너무 많은 시도 후에도 배정 못하면 중복 무시하고 진행
            if (attempts >= maxAttempts) {
                printf("남성 배정 실패 후 중복 무시하고 진행: %s\n", Male[SelectedIdx].name);
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

// DuplCheck 함수 개선 - 반환값 의미 명확하게 수정
int DuplCheck(int n, int* arr) // 중복됨: 1(true), 중복되지않음: 0(false)
{
    if (n == -1) return 0; // 이전 팀이 없는 경우 중복 체크 안 함
    else
    {
        for (int i = 0; i < 5; i++)
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

//// Team 내에 중복을 확인하는 함수
//int DuplCheck(int n, int* arr) //중복됨:1, 중복되지않음:0
//{
//    if (n == -1) return 0; // 이전 팀이 없는 경우 중복 체크 안 함
//    else
//    {
//        int count = 0;//중복 수
//        
//        for (int i = 0; i < 5; i++)
//        {
//            if (arr[i] == n)
//            {
//                count++;
//            }
//        }
//        return count>0;//중복 허용 수 조절 가능 (빠진 인원 만큼 조정)
//    }
//}
//전체인원을 성별에 따라 분류하는 함수
void Classification(MEMBER* Tptr, MEMBER* Mptr, MEMBER* Fptr, MEMBER* temp, const int size, int* FCount, int* MCount, int* TCount)		// size는 Tptr배열의 크기
{
    *FCount = 0; //여성 수
    *MCount = 0; //남성 수
    *TCount = 0; //이외 인원 수

    for (int i = 0; i < size; i++)
    {
        if (Tptr[i].gender == 'f')
        {
            Fptr[*FCount] = Tptr[i];
            ++(*FCount);
        }
        else if (Tptr[i].gender == 'm')
        {
            Mptr[*MCount] = Tptr[i];
            ++(*MCount);
        }
        else if (Tptr[i].gender == 'N')
        {
            temp[*TCount] = Tptr[i];
            ++(*TCount);
        }
        else if (Tptr[i].gender == 'E')
        {
            temp[*TCount] = Tptr[i];
            ++(*TCount);
        }
    }
}

// // 입력 파일에서 MEMBER 배열을 읽어오는 함수
// void ReadOrigin(MEMBER* members, const char* file_name) {
//     FILE* file = fopen(file_name, "r");
//     if (!file) {
//         perror("파일을 열 수 없습니다.");
//         exit(1);
//     }

//     int idx = 0;
//     while (fscanf(file, "%s %d %c", members[idx].name, &members[idx].prev_team, &members[idx].gender) == 3) {
//         idx++;
//     }
//     fclose(file);
// }


// gcc makegroup.c -o group_maker 이거로 실행파일 만들 수 있음
void ReadOrigin(MEMBER* members, const char* file_name) {
    FILE* file = fopen(file_name, "r");
    if (!file) {
        perror("파일을 열 수 없습니다.");
        exit(1);
    }

    int idx = 0;
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        int prev_team;
        char name[20], gender;
        char* token = strtok(line, " \n");

        if (token == NULL) continue;
        prev_team = atoi(token); // 첫번째 숫자=팀

        // 한 줄 씩 읽어옴
        while ((token = strtok(NULL, " \n")) != NULL) { 
            strncpy(name, token, sizeof(name));
            token = strtok(NULL, " \n");
            if (token == NULL) break; 
            gender = token[0];

            strncpy(members[idx].name, name, sizeof(members[idx].name));
            members[idx].gender = gender;
            members[idx].prev_team = prev_team;
            idx++;
        }
    }
    fclose(file);
}



// 출력 함수
void printOrigin(MEMBER* members, int count) {
    for (int idx = 0; idx < count; idx++) {
        printf("%d: %s %d %c\n", idx + 1, members[idx].name, members[idx].prev_team, members[idx].gender);
    }
}

void WriteText(TEAM* teams, MEMBER* Temp, int ab_num, int team_count, const char* file_name) {
    FILE* file = fopen(file_name, "w");
    if (!file) {
        perror("파일을 저장할 수 없습니다.");
        exit(1);
    }
    //결석자 출력(0조)
    fprintf(file, "%d ", 0); // 팀 번호 출력
    for (int i = 0; i < ab_num; i++) {
        fprintf(file, "%s %c ", Temp[i].name, Temp[i].gender);
    }
    fprintf(file, "\n"); // 각 팀의 멤버 출력 후 줄바꿈

    //조편성 출력
    for (int i = 0; i < team_count; i++) {
        fprintf(file, "%d ", i + 1); // 팀 번호 출력
        for (int j = 0; j < teams[i].count; j++) {
            fprintf(file, "%s %c ", teams[i].member[j].name, teams[i].member[j].gender);
        }
        fprintf(file, "\n"); // 각 팀의 멤버 출력 후 줄바꿈
    }
    fclose(file);

    // 콘솔 출력
    for (int i = 0; i < team_count; i++) {
        printf("%d ", i + 1); // 팀 번호 출력
        for (int j = 0; j < teams[i].count; j++) {
            printf("%s %c ", teams[i].member[j].name, teams[i].member[j].gender);
        }
        printf("\n"); // 각 팀의 멤버 출력 후 줄바꿈
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

void Genderchange(MEMBER* Temp, int size)
{
    // 결석자 이름을 찾고 성별 수정
    for (int i = 0; i < size; i++) {
        if (Temp[i].gender == 'N')
            Temp[i].gender = 'M';
        else if (Temp[i].gender == 'E')
            Temp[i].gender = 'F';
    }
}

int Absent(MEMBER* member, char* ab_name)
{
    int absent_num = 0;
    char* name = strtok(ab_name, ",");
    while (name != NULL) {
        absent_num++;  // 결석자 수 증가

        // 결석자 이름을 찾고 성별 수정
        for (int i = 0; i < 30; i++) { //전체 인원 돌리면서 해당 인원 추출
            if (strcmp(name, member[i].name) == 0) {
                if (member[i].gender == 'M')
                    member[i].gender = 'N';// 결석할 남자 -> N으로 변경
                else if (member[i].gender == 'F')
                    member[i].gender = 'E';  // 결석할 여자 -> E로 변경

            }
        }
        name = strtok(NULL, ",");
    }
    return absent_num;
}

// 남성과 여성 배열을 출력하는 함수
void PrintMembers(MEMBER* Male, int Mcount, MEMBER* Female, int Fcount) {
    printf("남성 멤버:\n");
    for (int i = 0; i < Mcount; i++) {
        printf("%s %d %c\n", Male[i].name, Male[i].prev_team, Male[i].gender);
    }

    printf("\n여성 멤버:\n");
    for (int i = 0; i < Fcount; i++) {
        printf("%s %d %c\n", Female[i].name, Female[i].prev_team, Female[i].gender);
    }
}