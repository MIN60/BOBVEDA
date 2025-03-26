#include <stdio.h>
#include <string.h>
#include <time.h>
#include "struct.h"

//�� ���� �������� ���� �����Ͽ� ���� ¥�� �Լ�
void TeamSelect(TEAM* Team, MEMBER* Male, MEMBER* Female, int Mcount, int Fcount) {
	int* FemaleIdx = CreateNumArr(Fcount);
	int* MaleIdx = CreateNumArr(Mcount);

	int LastIndex = 6;//�� �� �ε���
	int idx = 0;//���� ��

	int RemainingF = Fcount;//���� ���� �ο� ��
	int RemainingM = Mcount;//���� ���� �ο� ��

	int SelectedIdx;//���õ� ��ȣ(�ڸ�)

	for (int i = 0; i < 7; i++)//�ο� 0���� �ʱ�ȭ
		Team[idx++].count = 0;

	for (int i = 0; i < Fcount; ) { //���� ��� �������� �ݺ�
		SelectedIdx = FemaleIdx[RandomNumber(RemainingF)];

		if (!DuplCheck(Female[SelectedIdx].prev_team, Team[idx].set)) {//�ߺ� �� Ȯ��
			continue; //����÷
		}

		int teamIdx = idx % (LastIndex + 1);
		Team[teamIdx].member[(Team[teamIdx].count)++] = Female[SelectedIdx];//��� ����, ��� �� ����
		Team[teamIdx].set[Team[teamIdx].count] = Female[SelectedIdx].prev_team; //���� �� set�� ������Ʈ

		ArrUpdate(FemaleIdx, RemainingF, SelectedIdx); //�迭 ���
		RemainingF--; //���� ���� �ο� ����
		i++;
		idx++;
		
	}

	for (int i = 0; i < Mcount; ) {
		SelectedIdx = MaleIdx[RandomNumber(RemainingM)];

		if (Male[SelectedIdx].prev_team == idx % (LastIndex + 1)) {
			continue;
		}

		int teamIdx = idx % (LastIndex + 1);
		Team[teamIdx].member[(Team[teamIdx].count)++] = Male[SelectedIdx];//��� ����, ��� �� ����
		Team[teamIdx].set[Team[teamIdx].count] = Female[SelectedIdx].prev_team; //���� �� set�� ������Ʈ

		ArrUpdate(MaleIdx, RemainingM, SelectedIdx); //�迭 ���
		RemainingM--; //���� ���� �ο� ����
		i++;
		idx++;
	}

	free(FemaleIdx);
	free(MaleIdx);
}
