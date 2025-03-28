#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>//check if it's unnecessary

#include "ong_struct.h"

void ReadOrigin(MEMBER* members, const char* file_name);
void printOrigin(MEMBER* members, int count);
void PrintMembers(MEMBER* Male, MEMBER* Female, MEMBER* Temp, int Mcount, int Fcount, int Tcount);
void WriteText(TEAM* teams, MEMBER* Temp, int ab_num, int team_count, const char* file_name);