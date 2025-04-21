#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "struct.h"
#include "randomize.h"
//�� ���� �������� ���� ����Ͽ� ���� ¥�� �Լ�
// TeamSelect �Լ� ����
int TeamSelect(TEAM* Team, MEMBER* Male, MEMBER* Female, int Mcount, int Fcount, int team_count) {
    int* FemaleIdx = CreateNumArr(Fcount);
    int* MaleIdx = CreateNumArr(Mcount);
    int LastIndex = team_count - 1; // ������ �� �ε���
    int idx = 0; // ���� ��
    int RemainingF = Fcount; // ���� ���� �ο� ��
    int RemainingM = Mcount; // ���� ���� �ο� ��
    int SelectedIdx; // ���õ� ��ȣ(�ڸ�)
    int wcount = 0;
    int mcount = 0;
    for (int i = 0; i < team_count; i++) // �� �� �ο� 0���� �ʱ�ȭ
    {
        Team[i].count = 0;
    }
    // ���� �߰� - ���� ������ �� ���� �ִ��� �յ��ϰ� ���
    for (int i = 0; i < Fcount;) {
        // ������ġ: �ʹ� ���� �õ� �Ŀ��� ���� ���ϸ� �ߺ� üũ �����ϰ� ����
        int attempts = 0;
        int maxAttempts = 50; // �ִ� �õ� Ƚ�� ����
        while (attempts < maxAttempts) {
            int Random_Idx = RandomNumber(RemainingF); // ���� Idx ����
            SelectedIdx = FemaleIdx[Random_Idx]; // ���� ��� �� ����
            int teamIdx = idx % team_count; // �� �ε����� ��ȯ�ϵ��� ����
            if (!DuplCheck(Female[SelectedIdx].prev_team, Team[teamIdx].set)) {
                // �ߺ� ���� - ���� ����
                wcount++;
                Team[teamIdx].member[(Team[teamIdx].count)] = Female[SelectedIdx]; // ��� ����, ��� �� ����
                Team[teamIdx].set[Team[teamIdx].count] = Female[SelectedIdx].prev_team; // ���� �� set�� ������Ʈ
                Team[teamIdx].count++;
                ArrUpdate(&FemaleIdx, &RemainingF, Random_Idx); // �迭 ����
                idx++; // �������� �̵�
                i++;
                break; // ���������� ���� while ���� Ż��
            }
            attempts++;
            // ������ġ: �ʹ� ���� �õ� �Ŀ��� ���� ���ϸ� �ߺ� �����ϰ� ����
            if (attempts >= maxAttempts) {
                //printf("���� ���� ���� �� �ߺ� �����ϰ� ����: %s\n", Female[SelectedIdx].name);
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
    // ���� �߰� - ������ ������ ������� ������ġ �߰�
    for (int i = 0; i < Mcount;) {
        int attempts = 0;
        int maxAttempts = 50; // �ִ� �õ� Ƚ�� ����
        while (attempts < maxAttempts) {
            int Random_Idx = RandomNumber(RemainingM); // ���� Idx ����
            SelectedIdx = MaleIdx[Random_Idx]; // ���� ��� �� ����
            int teamIdx = idx % team_count; // �� �ε����� ��ȯ�ϵ��� ����
            if (!DuplCheck(Male[SelectedIdx].prev_team, Team[teamIdx].set)) {
                // �ߺ� ���� - ���� ����
                mcount++;
                Team[teamIdx].member[(Team[teamIdx].count)] = Male[SelectedIdx]; // ��� ����, ��� �� ����
                Team[teamIdx].set[Team[teamIdx].count] = Male[SelectedIdx].prev_team; // ���� �� set�� ������Ʈ
                Team[teamIdx].count++;
                ArrUpdate(&MaleIdx, &RemainingM, Random_Idx); // �迭 ����
                idx++; // �������� �̵�
                i++;
                break; // ���������� ���� while ���� Ż��
            }
            attempts++;
            // ������ġ: �ʹ� ���� �õ� �Ŀ��� ���� ���ϸ� �ߺ� �����ϰ� ����
            if (attempts >= maxAttempts) {
                //printf("���� ���� ���� �� �ߺ� �����ϰ� ����: %s\n", Male[SelectedIdx].name);
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
    return 0; // ���� ����
}
// �ߺ��� �˻��ϴ� �Լ�
int DuplCheck(int n, int* arr) // �ߺ���: 1(true), �ߺ���������: 0(false)
{
    if (n == -1) return 0; // ���� ���� ���� ��� �ߺ� üũ �� ��
    else
    {
        for (int i = 0; i < 5; i++) // �ִ� 5����� üũ
        {
            if (arr[i] == n)
            {
                return 1; // �ߺ� �߰�
            }
        }
        return 0; // �ߺ� ����
    }
}
void InitRandom() {
    srand(time(NULL)); // ���α׷� ���� �� �� ���� ����
}
// 0 ~ num-1�� ���� ���
int RandomNumber(int num) {
    if (num <= 0) return -1; // ���� ��ġ
    return rand() % num;
}
// ���� ���� �迭 ����
int* CreateNumArr(int num) {
    int* new_arr = malloc(sizeof(int) * num);
    for (int i = 0; i < num; i++) {
        new_arr[i] = i;
    }
    return new_arr;
}
// ��ü�ο��� ������ ���� �з��ϴ� �Լ�
void Classification(MEMBER* Tptr, MEMBER* Mptr, MEMBER* Fptr, MEMBER* temp, const int size, int* FCount, int* MCount, int* TCount)
{
    *FCount = 0; // ���� ��
    *MCount = 0; // ���� ��
    *TCount = 0; // �̿� �ο� ��
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
    // ���õ� �ε����� ���� ������ ���� ��ȯ
    int temp = (*arr)[index];
    (*arr)[index] = (*arr)[*size - 1];
    (*arr)[*size - 1] = temp;
    // ũ�� ����
    (*size)--;
    // �迭�� ũ�⸦ ����
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
// ������ ���� �迭�� ����ϴ� �Լ�
void PrintMembers(MEMBER* Male, MEMBER* Female, MEMBER* Temp, int Mcount, int Fcount, int Tcount) {
    printf("���� ���:\n");
    for (int i = 0; i < Mcount; i++) {
        printf("%s %d %c\n", Male[i].name, Male[i].prev_team, Male[i].gender);
    }
    printf("\n���� ���:\n");
    for (int i = 0; i < Fcount; i++) {
        printf("%s %d %c\n", Female[i].name, Female[i].prev_team, Female[i].gender);
    }
    printf("\n���� �ο�:\n");
    for (int i = 0; i < Tcount; i++) {
        printf("%s %d %c\n", Temp[i].name, Temp[i].prev_team, Temp[i].gender);
    }
}