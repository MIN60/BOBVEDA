#ifndef _ONG_RANDOMIZE_H_
#define _ONG_RANDOMIZE_H_

#include <time.h>
#include <stdlib.h>
 
#include "ong_struct.h"

void InitRandom();
int RandomNumber(int num);
int TeamSelect(TEAM* Team, MEMBER* Male, MEMBER* Female, int Mcount, int Fcount);
int* CreateNumArr(int num);
int DuplCheck(int n, int* arr);
void ArrUpdate(int** arr, int* size, int index);
void Classification(MEMBER* Tptr, MEMBER* Mptr, MEMBER* Fptr, MEMBER* temp, const int size, int* FCount, int* MCount, int* TCount);

#endif