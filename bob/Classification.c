#ifndef _CLASS_H_
#define _CLASS_H_

#include "struct.h"

//성별 분류하는 함수 (Tptr: 순환, Mptr: 남성, Fptr: 여성)
void Classification(MEMBER* Tptr, MEMBER* Mptr, MEMBER* Fptr)
{
	int FCount=0, //여성 수
		MCount = 0;//남성 수

	for (int i = 0; sizeof(Mptr) / sizeof(Mptr[0]);i++)
	{
		if (Mptr[i].gender == 'f')
		{
			FCount++;

		}
		elif(Mptr[i].gender == 'm')


	}
	
	//Female 분류
	count
	Mptr[]
}
#endif