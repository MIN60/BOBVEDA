#include <stdio.h>
#include <string.h>
#include "struct.h"
#include "file.h"

//Team���� �ߺ��� Ȯ���ϴ� �Լ�
int DuplCheck(int n, int *arr) //�ߺ���:1, �ߺ���������:0
{
	int count = 0;//�ߺ� ��
	for (int i = 0;i < 5;i++)
		if (arr[i] == n)
			count++;
	return count;//�ߺ� ��� �� ���� ����
}