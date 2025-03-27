#ifndef _CLASS_H_
#define _CLASS_H_
#include "file.h"
#include "struct.h"

//���� �з��ϴ� �Լ� (Tptr: ��ȯ, Mptr: ����, Fptr: ����)
void Classification(MEMBER* Tptr, MEMBER* Mptr, MEMBER* Fptr, const int size, int* FCount, int* MCount)		// size�� Tptr�迭�� ũ��
{
	*FCount = 0; //���� ��
	*MCount = 0; //���� ��

	for (int i = 0; i < size; i++)
	{
		if (Tptr[i].gender == 'F')
		{
			Fptr[*FCount] = Tptr[i];
			++(*FCount);
		}
		else if (Tptr[i].gender == 'M')
		{
			Mptr[*MCount] = Tptr[i];
			++(*MCount);
		}
	}
}
#endif