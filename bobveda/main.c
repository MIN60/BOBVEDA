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
        printf("사용법: ./group_maker input.txt excludeList output.txt\n");
        return 1;
    }

    const char* input_file = argv[1];
    const char* exclude_list = argv[2];
    const char* output_file = argv[3];

    printf("입력 파일: %s\n", input_file);
    printf("제외 목록: %s\n", exclude_list);
    printf("출력 파일: %s\n", output_file);

    MEMBER member[30]; // 전체 멤버
    MEMBER absent[256]; // 제외된 멤버
    MEMBER Male[30], Female[30], Temp[30]; // 성별 분류
    int Mcount, Fcount, Tcount;

    // 입력 파일 읽기
    ReadOrigin(member, input_file);

    // 읽어온 멤버 출력
    printf("\n읽어온 전체 멤버 목록:\n");
    for (int i = 0; i < 30; i++) {
        if (member[i].name[0] != '\0') {  // 비어있지 않은 항목만 출력
            printf("%d: %s (%c)\n", i + 1, member[i].name, member[i].gender);
        }
    }

    // 제외자 처리
    char ab_copy[256];
    strncpy(ab_copy, exclude_list, sizeof(ab_copy));
    ab_copy[sizeof(ab_copy) - 1] = '\0';
    printf("\n제외자 처리 시작...\n");
    int ab_num = Absent(member, ab_copy);
    printf("제외자 처리 완료. 제외된 인원: %d명\n", ab_num);

    // 성별 분류
    Classification(member, Male, Female, Temp, 30, &Fcount, &Mcount, &Tcount);
    // 성별 분류 확인
    PrintMembers(Male, Female, Temp, Mcount, Fcount, Tcount);
    printf("제외된 인원 수: %d\n", Tcount);
    if (Tcount != ab_num) {
        printf("경고: 제외 인원 수 불일치 (ab_num=%d, Tcount=%d)\n", ab_num, Tcount);
    }

    // 결석자 성별 변환
    Genderchange(Temp, ab_num);

    // 팀 수 계산
    int total_members = Mcount + Fcount;
    int members_per_team = 4; // 기본 팀당 인원수
    int team_count = (total_members + members_per_team - 1) / members_per_team; // 올림 계산

    // 팀당 인원이 너무 적으면 3명으로 조정
    if (total_members / team_count < 3) {
        members_per_team = 3;
        team_count = (total_members + members_per_team - 1) / members_per_team;
    }

    printf("\n팀 구성 정보:\n");
    printf("총 인원: %d명 (남:%d, 여:%d)\n", total_members, Mcount, Fcount);
    printf("팀 수: %d, 팀당 인원: 약 %d명\n", team_count, members_per_team);

    // 팀 생성
    TEAM* teams = (TEAM*)malloc(sizeof(TEAM) * team_count);
    for (int i = 0; i < team_count; i++) {
        teams[i].member = (MEMBER*)malloc(sizeof(MEMBER) * (members_per_team + 1)); // 추가 인원 가능성
        if (!teams[i].member) {
            perror("Memory allocation failed");
            exit(1);
        }
        teams[i].count = 0;
        for (int j = 0; j < 10; j++) { // 충분히 큰 size로 초기화
            teams[i].set[j] = -1;
        }
    }

    // 팀 배정
    InitRandom();
    TeamSelect(teams, Male, Female, Mcount, Fcount, team_count);

    // 결과 파일 저장
    WriteText(teams, Temp, Tcount, team_count, output_file);

    // 메모리 해제
    for (int i = 0; i < team_count; i++) {
        free(teams[i].member);
    }
    free(teams);

    return 0;
}