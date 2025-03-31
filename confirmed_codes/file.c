#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
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
        prev_team = atoi(token);  


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


void printOrigin(MEMBER* members, int count) {
    for (int idx = 0; idx < count; idx++) {
        printf("%d: %s %d %c\n", idx + 1, members[idx].name, members[idx].prev_team, members[idx].gender);
    }
}


void PrintMembers(MEMBER* Male, MEMBER* Female, MEMBER* Temp, int Mcount, int Fcount, int Tcount) {
    printf("남성 멤버:\n");
    for (int i = 0; i < Mcount; i++) {
        printf("%s %d %c\n", Male[i].name, Male[i].prev_team, Male[i].gender);
    }
    printf("\n여성 멤버:\n");
    for (int i = 0; i < Fcount; i++) {
        printf("%s %d %c\n", Female[i].name, Female[i].prev_team, Female[i].gender);
    }
    printf("\n제외 인원:\n");
    for (int i = 0; i < Tcount; i++) {
        printf("%s %d %c\n", Temp[i].name, Temp[i].prev_team, Temp[i].gender);
    }
}

void WriteText(TEAM* teams, MEMBER* Temp, int ab_num, int team_count, const char* file_name) {
    FILE* file = fopen(file_name, "w");
    if (!file) {
        perror("파일을 저장할 수 없습니다.");
        exit(1);
    } 

    if (ab_num > 0) {
        fprintf(file, "%d ", 0);  
        for (int i = 0; i < ab_num; i++) {
            fprintf(file, "%s %c ", Temp[i].name, Temp[i].gender);
        }
        fprintf(file, "\n");  
    }

     
    for (int i = 0; i < team_count; i++) {
        fprintf(file, "%d ", i + 1);  
        for (int j = 0; j < teams[i].count; j++) {
            fprintf(file, "%s %c ", teams[i].member[j].name, teams[i].member[j].gender);
        }
        fprintf(file, "\n"); 
    }
    fclose(file);

    
    for (int i = 0; i < team_count; i++) {
        printf("%d ", i + 1);  
        for (int j = 0; j < teams[i].count; j++) {
            printf("%s %c ", teams[i].member[j].name, teams[i].member[j].gender);
        }
        printf("\n");  
    }
}
