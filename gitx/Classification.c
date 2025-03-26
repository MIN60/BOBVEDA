#ifndef _CLASS_H_
#define _CLASS_H_

#include "struct.h"

//성별 분류하는 함수 (Tptr: 순환, Mptr: 남성, Fptr: 여성)
void Classification(MEMBER* Tptr, MEMBER* Mptr, MEMBER* Fptr, const int size, int* FCount, int* MCount)		// size는 Tptr배열의 크기
{
	*FCount = 0; //여성 수
	*MCount = 0; //남성 수

	for (int i = 0; i < size; i++)
	{
		if (Tptr[i].gender == 'f')
		{
			Fptr[*FCount] = Tptr[i];
			++(*FCount);
		}
		else if (Tptr[i].gender == 'm')
		{
			Mptr[*MCount] = Tptr[i];
			++(*MCount);
		}
	}
}
#endif