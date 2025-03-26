
#include <stdio.h>
#include <string.h>
#include "struct.h"
#include "main.h"

/*
* 		for (int i = 0; i < cnt; i++)
		{
			if (!(strcmp(str, profile[i].name))
			{
				strcpy(profile[i].name, "-1");
			}
		} 
*/

void delete()
{
	char str[40];

	while (1)
	{
		printf("삭제할 사람 입력: "); gets(str);
		if (str == "0") return;//안할거면 0

		for (int i = 0; i < cnt; i++)
		{
			if (!strcmp(str, profile[i].name))
			{
				strcpy(profile[i].name, "-1");//삭제할 인덱스의 배열에 -1 넣기
				break;
			}
			else if (i == cnt - 1) printf("잘못된 입력\n");
		}
	}

	return;
}