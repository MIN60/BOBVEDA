#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "my_rand.h"
#include "struct2.h"

#define NUM 28 //최대 명수

//typedef struct Person
//{
//    wchar_t name[20];
//    char gender;
//    unsigned char id;
//    unsigned int prev_team;
//
//} Person;



int main(/*char* absentee*/)
{
    //이하 2줄은 혼자 디버깅할 때 테스트용
    char ex_str[] = "kim,jang";  // 결석자 목록
    char* absentee = ex_str;     // 단일 문자열 포인터
     
    Person people[NUM];  


    FILE* fp = fopen("origin.txt", "r");
    if (fp == NULL) {
        perror("File opening failed");
        return 1;  
    }
     
    for (int i = 0; i < NUM; i++) {
        fscanf(fp, "%s %c\n", people[i].name, &people[i].gender);
    }
     
    fclose(fp);

    int absent_num = 0;  // 결석자 수
    char tmp[128] = "";
     
    char* name = strtok(absentee, ",");
    while (name != NULL) {
        absent_num++;  // 결석자 수 증가

        // 결석자 이름을 찾고 성별 수정
        for (int i = 0; i < NUM; i++) {
            if (strcmp(name, people[i].name) == 0) {   
                if (people[i].gender == 'M')
                    people[i].gender = 'N';  // 결석할 남자 -> N으로 변경
                else if (people[i].gender == 'F')
                    people[i].gender = 'E';  // 결석할 여자 -> E로 변경
            }
        } 
        name = strtok(NULL, ",");
    }

    // 확인상: 각 구조체의 모든 멤버를 한 줄로 출력(결석자 성별 N, E로 변경)
    for (int i = 0; i < NUM; i++) {
        printf("%s %c\n", people[i].name, people[i].gender);
    }
    printf("----FOR TEST\n\n");

    // ID 셔플
    char input;

    while (1)
    {
        printf("continue (y)");
        scanf("%c", &input);

        my_srand((unsigned int)time(0));

        int indices[28];
        for (int i = 0; i < 28; i++)
            indices[i] = i;

        shuffle(indices, 28);

        // 팀 구성: 7팀, 각 팀 4명
        Person team[7][4];

        for (int i = 0; i < 28; i++)
        {
            int team_index = i / 4;
            int member_index = i % 4;

            team[team_index][member_index] = people[indices[i]];
        }


        // 결과 출력
        for (int i = 0; i < 7; i++)
        {
            int f_count = 0, m_count = 0;
            printf("Team %d:\n", i + 1);
            for (int j = 0; j < 4; j++)
            {
                printf("%s (%c)   ", team[i][j].name, team[i][j].gender);
                //printf("  Name: %s, Gender: %c\n", team[i][j].name, team[i][j].gender);
                //fprintf(fp, "%s\t%c\n", team[i][j].name, team[i][j].gender);
                if (team[i][j].gender == 'F')
                    f_count++;
                else
                    m_count++;
            }
            printf("\tmale: %d female: %d", m_count, f_count);
            printf("\n\n");

        }

        printf("\n***************\n");
    }

    return 0;
}
