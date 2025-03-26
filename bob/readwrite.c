#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "struct.h"

//origin.txt 읽어오는 함수
void ReadOrigin(MEMBER* Optr, const char* file_name) {
	int n = 0;
	char name[20];
	char gender;

	FILE* fp = fopen(file_name, "r");
	if (!fp) {
		perror("'origin.txt' File open failed");
		exit(1);
	}

	while (fscanf(fp, "%s %c", name, &gender) == 2) {
		strcpy(Optr[n].name, name);  // 문자열 복사
		Optr[n].gender = gender;     // 성별 저장
		n++;  // 다음 인덱스로 이동
	}

	fclose(fp);

	// 데이터 출력 (읽은 개수만큼만 출력)
	for (int i = 0; i < n; i++)
		printf("%s %c\n", Optr[i].name, Optr[i].gender);
}

//prevTeam.txt 읽어오는 함수
void ReadPrev(MEMBER* Rptr, const char* file_name)
{
	FILE* fp = fopen(file_name, "r");
	if (!fp) {
		perror("'prev.txt' File open failed");
		exit(1);
	}
	for (;;) //조 순환하며
	{
		for (;;)//해당 인원 정보 업데이트
		{

		}
	}
	fclose(fp);
}

//bobveda-date.txt 내보내는 함수
void WriteText(TEAM* Wptr, const char* file_name)
{
	FILE* fp = fopen(file_name, "w");
	if (!fp) {
		perror("'prev.txt' File open failed");
		exit(1);
	}

	fclose(fp);
}