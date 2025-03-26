#ifndef _FILE_H_
#define _FILE_H_
#include "struct.h"

void TeamSelect(TEAM* Team, MEMBER* Male, MEMBER* Female, int Mcount, int Fcount);
void InitRandom();
int RandomNumber(int num);
int* CreateNumArr(int num);
void ArrUpdate(int** arr, int size, int index);
int DuplCheck(int n, int* arr);
void Classification(MEMBER* Tptr, MEMBER* Mptr, MEMBER* Fptr, const int size, int* FCount, int* MCount);

#endif