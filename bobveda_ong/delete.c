
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
		printf("������ ��� �Է�: "); gets(str);
		if (str == "0") return;//���ҰŸ� 0

		for (int i = 0; i < cnt; i++)
		{
			if (!strcmp(str, profile[i].name))
			{
				strcpy(profile[i].name, "-1");//������ �ε����� �迭�� -1 �ֱ�
				break;
			}
			else if (i == cnt - 1) printf("�߸��� �Է�\n");
		}
	}

	return;
}