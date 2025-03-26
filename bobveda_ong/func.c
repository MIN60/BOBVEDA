
#include <stdio.h>
#include <string.h>
#include "struct.h"
#include "main.h"

void Search()
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

void Remove()
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
				break;
			}
			else if (i == cnt - 1) printf("잘못된 입력\n");
		}
	}

	return;
}

void Randomize()
{
	printf("randomize~\n");
}