#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "struct.h"
#include "file.h"



int main()
{
    MEMBER member[30];//30명 기준
    // ReadOrigin(member, "origin.txt");

    // 성별 분류
    MEMBER Male[30], Female[30];
    int Mcount, Fcount;
    Classification(member, Male, Female, 30, &Fcount, &Mcount);

    // 팀 생성
    TEAM teams[7];
    for (int i = 0; i < 7; i++) {
        teams[i].member = (MEMBER*)malloc(sizeof(MEMBER) * 5); // 최대 5명 할당
        teams[i].count = 0;
        for (int j = 0; j < 5; j++) {
            teams[i].set[j] = -1;
        }
    }

    // 팀 배정
    InitRandom();
    TeamSelect(teams, Male, Female, Mcount, Fcount);

    // 결과 출력
    // WriteText(teams, "output.txt");

    // 메모리 해제
    for (int i = 0; i < 7; i++) {
        free(teams[i].member);
    }

    return 0;
}
