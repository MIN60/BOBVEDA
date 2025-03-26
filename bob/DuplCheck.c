#include <stdio.h>
#include <string.h>
#include "struct.h"
#include "file.h"

//Team내에 중복을 확인하는 함수
int DuplCheck(int n, int *arr) //중복됨:1, 중복되지않음:0
{
	int count = 0;//중복 수
	for (int i = 0;i < 5;i++)
		if (arr[i] == n)
			count++;
	return count;//중복 허용 수 조절 가능
}