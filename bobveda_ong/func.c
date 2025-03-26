
#include <stdio.h>
#include <string.h>
#include "struct.h"
#include "main.h"

void search()
{
	char str[40];

	while (1)
	{
		printf("찾을 멤버 이름 입력: "); fgets(str, sizeof(str), stdin);//gets(str);
		if (strcmp(str,"0")==0) return;//안할거면 0

		for (int i = 0; i < cnt; i++)
		{
			if (!strcmp(str, profile[i].name))
			{
				printf("%s %c %d\n", profile[i].name, profile[i].gender, profile[i].ex_team);
				break;
			}
			else if(i==cnt-1) printf("%s은(는) 대상 리스트에 없습니다.\n", str);
		}
	}

	return  ;
}

void remove()
{
	char str[40];

	while (1)
	{
		printf("삭제할 사람 입력: "); fgets(str, sizeof(str), stdin);//gets(str);
		if (strcmp(str, "0") == 0) return;//안할거면 0

		for (int i = 0; i < cnt; i++)
		{
			if (!strcmp(str, profile[i].name))
			{
				profile[i].is_deleted = 1;
				//strcpy(profile[i].name, "0");//삭제할 인덱스의 배열에 -1 넣기
				break;
			}
			else if (i == cnt - 1)
			{
				printf("잘못된 입력\n");
			}
		}
	}

	return;
}

void randomize()
{
	printf("randomize~\n");
}