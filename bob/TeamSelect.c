#include <stdio.h>
#include <string.h>
#include <time.h>
#include "struct.h"

//각팀에 이전조와 중복없이 넣는 함수
void TeamSelect(TEAM * Team, MEMBER * Male, MEMBER* Female)
{
	int Mcount = (sizeof(Male) / sizeof(Male[0])); //남자 수
	int Fcount = (sizeof(Female) / sizeof(Female[0]));//여자 수
	int NotSelect = Mcount + Fcount;//선택되지 않은 사람의 수
	int* FemaleIdx = CreateNumArr(Fcount);//남자에게 배분
	int* MaleIdx = CreateNumArr(Fcount);

	int LastIndex = (30/4)-1;//마지막 조의 인덱스
	int idx = 0;//현재 조

	int SelectedIdx; //선택된 번호(자리)

	for (int i = 0; i < Fcount; Fcount--) //선택되지 않은 여자가 없을 때까지 반복
	{

		SelectedIdx = FemaleIdx[RandomNumber(Fcount)]; //무작위로 선택된 idx(n번째 쪽지)
		if (Female[SelectedIdx].prev_team == SelectedIdx%(LastIndex+1)) //중복 됐다면
		{
			Fcount++; //재추첨
			continue;
		}
		else
			ArrUpdate(FemaleIdx, Fcount, SelectedIdx); //해당 Idx 제거 후 배열 축소
	}

	for (int i = 0; i < Mcount; Mcount--) //선택되지 않은 남자가 없을 때까지 반복
	{

	}

	free(); //Fidx
	free(); //Midx
}