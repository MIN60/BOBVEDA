#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "struct.h"

//origin.txt �о���� �Լ�
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
		strcpy(Optr[n].name, name);  // ���ڿ� ����
		Optr[n].gender = gender;     // ���� ����
		n++;  // ���� �ε����� �̵�
	}

	fclose(fp);

	// ������ ��� (���� ������ŭ�� ���)
	for (int i = 0; i < n; i++)
		printf("%s %c\n", Optr[i].name, Optr[i].gender);
}

//prevTeam.txt �о���� �Լ�
void ReadPrev(MEMBER* Rptr, const char* file_name)
{
	FILE* fp = fopen(file_name, "r");
	if (!fp) {
		perror("'prev.txt' File open failed");
		exit(1);
	}
	for (;;) //�� ��ȯ�ϸ�
	{
		for (;;)//�ش� �ο� ���� ������Ʈ
		{

		}
	}
	fclose(fp);
}

//bobveda-date.txt �������� �Լ�
void WriteText(TEAM* Wptr, const char* file_name)
{
	FILE* fp = fopen(file_name, "w");
	if (!fp) {
		perror("'prev.txt' File open failed");
		exit(1);
	}

	fclose(fp);
}