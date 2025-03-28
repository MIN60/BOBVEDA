#include <time.h>
#include <stdlib.h>
 
#include "ong_struct.h"
#include "ong_randomize.h"

void InitRandom() {
    srand(time(NULL)); // ���α׷� ���� �� �� ���� ����
}

int RandomNumber(int num) {
    // 0 ~ num-1�� ���� ���
    if (num <= 0) return -1; // ���� ��ġ
    return rand() % num;
}

int TeamSelect(TEAM* Team, MEMBER* Male, MEMBER* Female, int Mcount, int Fcount) {

    int* FemaleIdx = CreateNumArr(Fcount);
    int* MaleIdx = CreateNumArr(Mcount);

    int LastIndex = 6;
    int idx = 0;

    int RemainingF = Fcount;//���� ���� �ο� ��
    int RemainingM = Mcount;//���� ���� �ο� ��

    int SelectedIdx;//���õ� ��ȣ(�ڸ�)
    int wcount = 0;
    int mcount = 0;

    for (int i = 0; i < 7; i++)//�� �� �ο� 0���� �ʱ�ȭ
    {
        Team[i].count = 0;
    }

    //���� ��÷
    for (int i = 0; i < Fcount;) {
        // ������ġ: �ʹ� ���� �õ� �Ŀ��� ���� ���ϸ� �ߺ� üũ �����ϰ� ����
        int attempts = 0;
        int maxAttempts = 50; // �ִ� �õ� Ƚ�� ����

        while (attempts < maxAttempts) {
            int Random_Idx = RandomNumber(RemainingF);//���� Idx ����
            SelectedIdx = FemaleIdx[Random_Idx]; //���� ��� �� ����
            int teamIdx = idx % (LastIndex + 1);

            if (!DuplCheck(Female[SelectedIdx].prev_team, Team[teamIdx].set)) {
                // �ߺ� ���� - ���� ����
                wcount++;
                Team[teamIdx].member[(Team[teamIdx].count)] = Female[SelectedIdx];//��� ����, ��� �� ����
                Team[teamIdx].set[Team[teamIdx].count] = Female[SelectedIdx].prev_team; //���� �� set�� ������Ʈ
                Team[teamIdx].count++;
                ArrUpdate(&FemaleIdx, &RemainingF, Random_Idx); //�迭 ���
                idx++; //�������� �̵�
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

    //���� ��÷ - ������ ������ ������� ������ġ �߰�
    for (int i = 0; i < Mcount;) {
        int attempts = 0;
        int maxAttempts = 50; // �ִ� �õ� Ƚ�� ����

        while (attempts < maxAttempts) {
            int Random_Idx = RandomNumber(RemainingM);//���� Idx ����
            SelectedIdx = MaleIdx[Random_Idx]; //���� ��� �� ����
            int teamIdx = idx % (LastIndex + 1);

            if (!DuplCheck(Male[SelectedIdx].prev_team, Team[teamIdx].set)) {
                // �ߺ� ���� - ���� ����
                mcount++;
                Team[teamIdx].member[(Team[teamIdx].count)] = Male[SelectedIdx];//��� ����, ��� �� ����
                Team[teamIdx].set[Team[teamIdx].count] = Male[SelectedIdx].prev_team; //���� �� set�� ������Ʈ
                Team[teamIdx].count++;
                ArrUpdate(&MaleIdx, &RemainingM, Random_Idx); //�迭 ���
                idx++; //�������� �̵�
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

int* CreateNumArr(int num) {
    // ���� ���� �迭 ����
    int* new_arr = malloc(sizeof(int) * num);
    for (int i = 0; i < num; i++) {
        new_arr[i] = i;
    }
    return new_arr;
}

int DuplCheck(int n, int* arr) // �ߺ���: 1(true), �ߺ���������: 0(false)
{
    //�ߺ��� �˻��ϴ� �Լ�
    if (n == -1) return 0; // ���� ���� ���� ��� �ߺ� üũ �� ��
    else
    {
        for (int i = 0; i < 5; i++)
        {
            if (arr[i] == n)
            {
                return 1; // �ߺ� �߰�
            }
        }
        return 0; // �ߺ� ����
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

void Classification(MEMBER* Tptr, MEMBER* Mptr, MEMBER* Fptr, MEMBER* temp, const int size, int* FCount, int* MCount, int* TCount)		// size�� Tptr�迭�� ũ��
{//��ü�ο��� ������ ���� �з��ϴ� �Լ�
    *FCount = 0; //���� ��
    *MCount = 0; //���� ��
    *TCount = 0; //�̿� �ο� ��

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
        else if (Tptr[i].gender == ('N' || 'E'))
        {
            temp[*TCount] = Tptr[i];
            ++(*TCount);
        }
    }
}