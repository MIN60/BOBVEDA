#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#include "randomize.h"
#include "struct.h"
#include "file.h"
#include "absent.h"


int main(int argc, char* argv[]) {
    if (argc < 4) {
        printf("누락: ./group_maker input.txt excludeList output.txt\n");
        return 1;
    }

    const char* input_file = argv[1];
    const char* exclude_list = argv[2];
    const char* output_file = argv[3];

    MEMBER member[30]; // 전체 멤버
    MEMBER absent[256]; // 제외된 멤버
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
    // 성별 분류 확인
    PrintMembers(Male, Female, Temp, Fcount, Mcount, Tcount);
    printf("ab_num: %d", Tcount);
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
    WriteText(teams, Temp, Tcount, 7, output_file);

    // 메모리 해제
    for (int i = 0; i < 7; i++) {
        free(teams[i].member);
    }

    return 0;
}
