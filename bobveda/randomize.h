#ifndef _RANDOMIZE_H_
#define _RANDOMIZE_H_
#include <time.h>
#include <stdlib.h>
#include "struct.h"
void InitRandom();
int RandomNumber(int num);
void Classification(MEMBER* Tptr, MEMBER* Mptr, MEMBER* Fptr, MEMBER* temp, const int size, int* FCount, int* MCount, int* TCount);
int* CreateNumArr(int num);
int TeamSelect(TEAM* Team, MEMBER* Male, MEMBER* Female, int Mcount, int Fcount, int team_count);
int DuplCheck(int n, int* arr);
void ArrUpdate(int** arr, int* size, int index);
#endif