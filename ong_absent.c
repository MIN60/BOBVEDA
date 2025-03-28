#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdlib.h>

#include "ong_struct.h" 
#include "ong_absent.h"

int Absent(MEMBER* member, char* ab_name)
{
    int absent_num = 0;
    char* name = strtok(ab_name, ",");
    while (name != NULL) {
        absent_num++;  // 결석자 수 증가
        // 결석자 이름을 찾고 성별 수정
        for (int i = 0; i < 30; i++) { //전체 인원 돌리면서 해당 인원 추출
            if (strcmp(name, member[i].name) == 0) {
                if (member[i].gender == 'M')
                    member[i].gender = 'N';// 결석할 남자 -> N으로 변경
                else if (member[i].gender == 'F')
                    member[i].gender = 'E';  // 결석할 여자 -> E로 변경
            }
        }
        name = strtok(NULL, ",");
    }
    return absent_num;
}

void Genderchange(MEMBER* Temp, int size)
{
    // 결석자 이름을 찾고 성별 수정
    for (int i = 0; i < size; i++) {
        if (Temp[i].gender == 'N')
            Temp[i].gender = 'M';
        else if (Temp[i].gender == 'E')
            Temp[i].gender = 'F';
    }
}