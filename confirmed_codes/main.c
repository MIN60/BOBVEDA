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
    if (argc < 4)
    {
        printf("´©¶ô: ./group_maker input.txt excludeList output.txt\n");
        return 1;
    }

    const char* input_file = argv[1];
    const char* exclude_list = argv[2];
    const char* output_file = argv[3];

    MEMBER member[30];  
    MEMBER absent[256];  
    MEMBER Male[30], Female[30], Temp[30];  
    int Mcount, Fcount, Tcount;
 
    ReadOrigin(member, input_file);
     
    char ab_copy[256];
    strncpy(ab_copy, exclude_list, sizeof(ab_copy));
    ab_copy[sizeof(ab_copy) - 1] = '\0';
    int ab_num = Absent(member, ab_copy);
     
    Classification(member, Male, Female, Temp, 30, &Fcount, &Mcount, &Tcount);
 
    PrintMembers(Male, Female, Temp, Fcount, Mcount, Tcount);   
    printf("ab_num: %d", Tcount); 
    Genderchange(Temp, ab_num);
     
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

    InitRandom();
    TeamSelect(teams, Male, Female, Mcount, Fcount);
     
    WriteText(teams, Temp, ab_num, 7, output_file);
     
    for (int i = 0; i < 7; i++) {
        free(teams[i].member);
    }

    return 0;
}