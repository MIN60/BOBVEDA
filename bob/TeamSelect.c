#include <stdio.h>
#include <string.h>
#include <time.h>
#include "struct.h"

//각 팀에 이전팀과 성비를 감안하여 조를 짜는 함수
void TeamSelect(TEAM* Team, MEMBER* Male, MEMBER* Female, int Mcount, int Fcount) {
	int* FemaleIdx = CreateNumArr(Fcount);
	int* MaleIdx = CreateNumArr(Mcount);

	int LastIndex = 6;//끝 조 인덱스
	int idx = 0;//현재 조

	int RemainingF = Fcount;//남은 여성 인원 수
	int RemainingM = Mcount;//남은 남성 인원 수

	int SelectedIdx;//선택된 번호(자리)

	for (int i = 0; i < 7; i++)//인원 0으로 초기화
		Team[idx++].count = 0;

	for (int i = 0; i < Fcount; ) { //남은 사람 기준으로 반복
		SelectedIdx = FemaleIdx[RandomNumber(RemainingF)];

		if (!DuplCheck(Female[SelectedIdx].prev_team, Team[idx].set)) {//중복 팀 확인
			continue; //재추첨
		}

		int teamIdx = idx % (LastIndex + 1);
		Team[teamIdx].member[(Team[teamIdx].count)++] = Female[SelectedIdx];//멤버 삽입, 멤버 수 증가
		Team[teamIdx].set[Team[teamIdx].count] = Female[SelectedIdx].prev_team; //현재 조 set을 업데이트

		ArrUpdate(FemaleIdx, RemainingF, SelectedIdx); //배열 축소
		RemainingF--; //남은 여성 인원 감소
		i++;
		idx++;
		
	}

	for (int i = 0; i < Mcount; ) {
		SelectedIdx = MaleIdx[RandomNumber(RemainingM)];

		if (Male[SelectedIdx].prev_team == idx % (LastIndex + 1)) {
			continue;
		}

		int teamIdx = idx % (LastIndex + 1);
		Team[teamIdx].member[(Team[teamIdx].count)++] = Male[SelectedIdx];//멤버 삽입, 멤버 수 증가
		Team[teamIdx].set[Team[teamIdx].count] = Female[SelectedIdx].prev_team; //현재 조 set을 업데이트

		ArrUpdate(MaleIdx, RemainingM, SelectedIdx); //배열 축소
		RemainingM--; //남은 남성 인원 감소
		i++;
		idx++;
	}

	free(FemaleIdx);
	free(MaleIdx);
}
