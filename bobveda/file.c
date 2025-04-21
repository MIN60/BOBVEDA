#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#include "file.h"
#include "struct.h"


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
    if (ab_num > 0) {
        fprintf(file, "%d ", 0); // 팀 번호 출력
        for (int i = 0; i < ab_num; i++) {
            fprintf(file, "%s %c ", Temp[i].name, Temp[i].gender);
        }
        fprintf(file, "\n"); // 각 팀의 멤버 출력 후 줄바꿈
    }

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
