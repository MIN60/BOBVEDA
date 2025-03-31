#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdlib.h>

#include "struct.h" 
#include "absent.h"

int Absent(MEMBER* member, char* ab_name)
{
    int absent_num = 0;
    char* name = strtok(ab_name, ",");
    while (name != NULL) {
        absent_num++;  

        for (int i = 0; i < 30; i++) {  
            if (strcmp(name, member[i].name) == 0) {
                if (member[i].gender == 'M')
                    member[i].gender = 'N'; 
                else if (member[i].gender == 'F')
                    member[i].gender = 'E';   
            }
        }
        name = strtok(NULL, ",");
    }
    return absent_num;
}

void Genderchange(MEMBER* Temp, int s)
{
    for (int i = 0; i < size; i++) {
        if (Temp[i].gender == 'N')
            Temp[i].gender = 'M';
        else if (Temp[i].gender == 'E')
            Temp[i].gender = 'F';
    }
}