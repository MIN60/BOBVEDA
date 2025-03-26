#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include "my_rand.h"

typedef struct Person
{
    wchar_t name[20];
    char gender;
    unsigned char id;
    unsigned int prev_team;

} Person;


int main()
{
    Person people[28];


    FILE* fp = fopen("origin.txt", "r");
    for (int i = 0; i < 28; i++)
    {
        fscanf(fp, "%s\n%c", people[i].name, &people[i].gender);
    }

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
