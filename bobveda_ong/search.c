
#include <stdio.h>
#include <string.h>
#include "struct.h"
#include "main.h"

void search()
{
	char str[40];

	while (1)
	{
		printf("찾을 멤버 이름 입력: "); gets(str);
		if (str == "0") return ;//안할거면 0

		for (int i = 0; i < cnt; i++)
		{
			if (!strcmp(str, profile[i].name))
			{
				printf("%s %c %d\n", profile[i].name, &profile[i].gender, &profile[i].ex_team);
				break;
			}
			else if(i==cnt-1) printf("%s은(는) 대상 리스트에 없습니다.\n", str);
		}
	}

	return  ;
}