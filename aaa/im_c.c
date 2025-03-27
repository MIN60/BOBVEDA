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
void WriteText(TEAM* teams, int team_count, const char* file_name);

void InitRandom();
int RandomNumber(int num);

int Absent(MEMBER* Absent, char* ab_name);
void Classification(MEMBER* Tptr, MEMBER* Mptr, MEMBER* Fptr, MEMBER* temp, const int size, int* FCount, int* MCount, int* TCount);
int* CreateNumArr(int num);
int TeamSelect(TEAM* Team, MEMBER* Male, MEMBER* Female, int Mcount, int Fcount);
int DuplCheck(int n, int* arr);
void ArrUpdate(int** arr, int* size, int index);

struct MEMBER {
    char name[20];
    int prev_team; // ���� ���� ������ ��� -1�� �ʱ�ȭ
    char gender; // f:female, m:male
};

struct TEAM {
    MEMBER* member; //member �߰��� �迭
    int set[5]; //�ߺ� checking�� �迭 -1�� �ʱ�ȭ
    int count; //��� ��, TeamSelect�Լ� ������ 0���� �ʱ�ȭ
};

int main() {
    MEMBER member[30]; //30�� ����
    ReadOrigin(member, "origin.txt");
    //printOrigin(member, 30); //��ü ��� �� ����

    //���� �з�
    MEMBER Male[30], Female[30], Temp[30];
    int Mcount, Fcount, Tcount;
    Classification(member, Male, Female,Temp, 30, &Fcount, &Mcount,&Tcount);

    //������ ���� �迭 ���
    //PrintMembers(Male, Mcount, Female, Fcount);

    //�� ����
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

    //�� ����
    InitRandom();
    TeamSelect(teams, Male, Female, Mcount, Fcount);/*
    while (TeamSelect(teams, Male, Female, Mcount, Fcount) == (-1))
    {
        printf("aaa");
        for (int i = 0; i < 7; i++) {
            memset(teams, 0, sizeof(teams));
        }

    }*/

    //��� ���
    WriteText(teams, 7, "output.txt");

    //�޸� ����
    for (int i = 0; i < 7; i++) {
        free(teams[i].member);
    }
    return 0;
}
//�� ���� �������� ���� �����Ͽ� ���� ¥�� �Լ�
//int TeamSelect(TEAM* Team, MEMBER* Male, MEMBER* Female, int Mcount, int Fcount) {
//
//    printf("select\n");
//    int* FemaleIdx = CreateNumArr(Fcount);
//    int* MaleIdx = CreateNumArr(Mcount);
//
//    int LastIndex = 6;//�� �� �ε���
//    int idx = 0;//���� ��
//
//    int RemainingF = Fcount;//���� ���� �ο� ��
//    int RemainingM = Mcount;//���� ���� �ο� ��
//
//    int SelectedIdx;//���õ� ��ȣ(�ڸ�)
//    int cnt = 0; //���� ���� Ȯ��
//
//
//    int wcount = 0;
//    int mcount = 0;
//
//
//    for (int i = 0; i < 7; i++)//�� �� �ο� 0���� �ʱ�ȭ
//    {
//        Team[idx+i].count = 0;
//    }
//
//    //���� ��÷
//    for (int i = 0; i < Fcount;) {
//        int Random_Idx = RandomNumber(RemainingF);//���� Idx ����
//        SelectedIdx = FemaleIdx[Random_Idx]; //���� ��� �� ����
//        int teamIdx = idx % (LastIndex + 1);
//
//        if (DuplCheck(Female[SelectedIdx].prev_team, Team[teamIdx].set)) {//�ߺ� �� Ȯ��
//            continue; //����÷
//        }
//        else
//        {
//            printf("���� ���� Ƚ�� %d\n", wcount++);
//            Team[teamIdx].member[(Team[teamIdx].count)] = Female[SelectedIdx];//��� ����, ��� �� ����
//            Team[teamIdx].set[Team[teamIdx].count] = Female[SelectedIdx].prev_team; //���� �� set�� ������Ʈ
//            Team[teamIdx].count++;
//            ArrUpdate(&FemaleIdx, &RemainingF, Random_Idx); //�迭 ���
//            idx++; //�������� �̵�
//            i++;
//        }
//    }
//
//    //���� ��÷
//    for (int i = 0; i < Mcount;) {
//        int Random_Idx = RandomNumber(RemainingM);//���� Idx ����
//        SelectedIdx = MaleIdx[Random_Idx]; //���� ��� �� ����
//        int teamIdx = idx % (LastIndex + 1);
//        if (DuplCheck(Male[SelectedIdx].prev_team, Team[teamIdx].set)) {//�ߺ� �� Ȯ��
//            continue;//����÷
//        }
//        else
//        {
//            printf("���� ���� Ƚ�� %d\n", mcount++);
//            Team[teamIdx].member[(Team[teamIdx].count)] = Male[SelectedIdx];//��� ����, ��� �� ����
//            Team[teamIdx].set[Team[teamIdx].count] = Male[SelectedIdx].prev_team; //���� �� set�� ������Ʈ
//            Team[teamIdx].count++;
//            ArrUpdate(&MaleIdx, &RemainingM, Random_Idx); //�迭 ���
//            idx++; //�������� �̵�
//            i++;
//        }
//    }
//
//   
//
//    free(FemaleIdx);
//    free(MaleIdx);
//}
// TeamSelect �Լ� ����
int TeamSelect(TEAM* Team, MEMBER* Male, MEMBER* Female, int Mcount, int Fcount) {
    printf("select\n");
    int* FemaleIdx = CreateNumArr(Fcount);
    int* MaleIdx = CreateNumArr(Mcount);

    int LastIndex = 6;//�� �� �ε���
    int idx = 0;//���� ��

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
                printf("���� ���� Ƚ�� %d\n", wcount++);
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
                printf("���� ���� ���� �� �ߺ� �����ϰ� ����: %s\n", Female[SelectedIdx].name);
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
                printf("���� ���� Ƚ�� %d\n", mcount++);
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
                printf("���� ���� ���� �� �ߺ� �����ϰ� ����: %s\n", Male[SelectedIdx].name);
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

// DuplCheck �Լ� ���� - ��ȯ�� �ǹ� ��Ȯ�ϰ� ����
int DuplCheck(int n, int* arr) // �ߺ���: 1(true), �ߺ���������: 0(false)
{
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

//// Team ���� �ߺ��� Ȯ���ϴ� �Լ�
//int DuplCheck(int n, int* arr) //�ߺ���:1, �ߺ���������:0
//{
//    if (n == -1) return 0; // ���� ���� ���� ��� �ߺ� üũ �� ��
//    else
//    {
//        int count = 0;//�ߺ� ��
//        
//        for (int i = 0; i < 5; i++)
//        {
//            if (arr[i] == n)
//            {
//                count++;
//            }
//        }
//        return count>0;//�ߺ� ��� �� ���� ���� (���� �ο� ��ŭ ����)
//    }
//}
//��ü�ο��� ������ ���� �з��ϴ� �Լ�
void Classification(MEMBER* Tptr, MEMBER* Mptr, MEMBER* Fptr, MEMBER* temp, const int size, int* FCount, int* MCount, int* TCount)		// size�� Tptr�迭�� ũ��
{
    *FCount = 0; //���� ��
    *MCount = 0; //���� ��
    *TCount = 0; //�̿� �ο� ��

    for (int i = 0; i < size; i++)
    {
        if (Tptr[i].gender== 'f')
        {
            Fptr[*FCount] = Tptr[i];
            ++(*FCount);
        }
        else if (Tptr[i].gender =='m')
        {
            Mptr[*MCount] = Tptr[i];
            ++(*MCount);
        }
        else if (Tptr[i].gender== 'N')
        {
            temp[*TCount] = Tptr[i];
            ++(*TCount);
        }
        else if (Tptr[i].gender== 'E')
        {
            temp[*TCount] = Tptr[i];
            ++(*TCount);
        }
    }
}

// �Է� ���Ͽ��� MEMBER �迭�� �о���� �Լ�
void ReadOrigin(MEMBER* members, const char* file_name) {
    FILE* file = fopen(file_name, "r");
    if (!file) {
        perror("������ �� �� �����ϴ�.");
        exit(1);
    }

    int idx = 0;
    while (fscanf(file, "%s %d %c", members[idx].name, &members[idx].prev_team, &members[idx].gender) == 3) {
        idx++;
    }
    fclose(file);
}

// ��� �Լ�
void printOrigin(MEMBER* members, int count) {
    for (int idx = 0; idx < count; idx++) {
        printf("%d: %s %d %c\n", idx + 1, members[idx].name, members[idx].prev_team, members[idx].gender);
    }
}

void WriteText(TEAM* teams, int team_count, const char* file_name) {
    FILE* file = fopen(file_name, "w");
    if (!file) {
        perror("������ ������ �� �����ϴ�.");
        exit(1);
    }

    for (int i = 0; i < team_count; i++) {
        fprintf(file, "%d ", i + 1); // �� ��ȣ ���
        for (int j = 0; j < teams[i].count; j++) {
            fprintf(file, "%s %c ", teams[i].member[j].name,teams[i].member[j].gender);
        }
        fprintf(file, "\n"); // �� ���� ��� ��� �� �ٹٲ�
    }
    fclose(file);

    // �ܼ� ���
    for (int i = 0; i < team_count; i++) {
        printf("%d ", i + 1); // �� ��ȣ ���
        for (int j = 0; j < teams[i].count; j++) {
            printf("%s %c ", teams[i].member[j].name,teams[i].member[j].gender);
        }
        printf("\n"); // �� ���� ��� ��� �� �ٹٲ�
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

int Absent(MEMBER* Absent, char* ab_name)
{
    int absent_num = 0;  // �Ἦ�� ��
    char tmp[128] = "";

    char* name = strtok(ab_name, ",");
    while (name != NULL) {
        absent_num++;  // �Ἦ�� �� ����

        // �Ἦ�� �̸��� ã�� ���� ����
        for (int i = 0; i < 30; i++) {
            if (strcmp(name, Absent[i].name) == 0) {
                if (Absent[i].gender == 'M')
                    Absent[i].gender = 'N';  // �Ἦ�� ���� -> N���� ����
                else if (Absent[i].gender == 'F')
                    Absent[i].gender = 'E';  // �Ἦ�� ���� -> E�� ����
            }
        }
        name = strtok(NULL, ",");
    }
    return absent_num;
}

// ������ ���� �迭�� ����ϴ� �Լ�
void PrintMembers(MEMBER* Male, int Mcount, MEMBER* Female, int Fcount) {
    printf("���� ���:\n");
    for (int i = 0; i < Mcount; i++) {
        printf("%s %d %c\n", Male[i].name, Male[i].prev_team, Male[i].gender);
    }

    printf("\n���� ���:\n");
    for (int i = 0; i < Fcount; i++) {
        printf("%s %d %c\n", Female[i].name, Female[i].prev_team, Female[i].gender);
    }
}