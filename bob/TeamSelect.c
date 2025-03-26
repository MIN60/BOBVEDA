#include <stdio.h>
#include <string.h>
#include <time.h>
#include "struct.h"

//������ �������� �ߺ����� �ִ� �Լ�
void TeamSelect(TEAM * Team, MEMBER * Male, MEMBER* Female)
{
	int Mcount = (sizeof(Male) / sizeof(Male[0])); //���� ��
	int Fcount = (sizeof(Female) / sizeof(Female[0]));//���� ��
	int NotSelect = Mcount + Fcount;//���õ��� ���� ����� ��
	int* FemaleIdx = CreateNumArr(Fcount);//���ڿ��� ���
	int* MaleIdx = CreateNumArr(Fcount);

	int LastIndex = (30/4)-1;//������ ���� �ε���
	int idx = 0;//���� ��

	int SelectedIdx; //���õ� ��ȣ(�ڸ�)

	for (int i = 0; i < Fcount; Fcount--) //���õ��� ���� ���ڰ� ���� ������ �ݺ�
	{

		SelectedIdx = FemaleIdx[RandomNumber(Fcount)]; //�������� ���õ� idx(n��° ����)
		if (Female[SelectedIdx].prev_team == SelectedIdx%(LastIndex+1)) //�ߺ� �ƴٸ�
		{
			Fcount++; //����÷
			continue;
		}
		else
			ArrUpdate(FemaleIdx, Fcount, SelectedIdx); //�ش� Idx ���� �� �迭 ���
	}

	for (int i = 0; i < Mcount; Mcount--) //���õ��� ���� ���ڰ� ���� ������ �ݺ�
	{

	}

	free(); //Fidx
	free(); //Midx
}