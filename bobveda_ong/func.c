
#include <stdio.h>
#include <string.h>
#include "struct.h"
#include "main.h"

void search()
{
	char str[40];

	while (1)
	{
		printf("ã�� ��� �̸� �Է�: "); fgets(str, sizeof(str), stdin);//gets(str);
		if (strcmp(str,"0")==0) return;//���ҰŸ� 0

		for (int i = 0; i < cnt; i++)
		{
			if (!strcmp(str, profile[i].name))
			{
				printf("%s %c %d\n", profile[i].name, profile[i].gender, profile[i].ex_team);
				break;
			}
			else if(i==cnt-1) printf("%s��(��) ��� ����Ʈ�� �����ϴ�.\n", str);
		}
	}

	return  ;
}

void remove()
{
	char str[40];

	while (1)
	{
		printf("������ ��� �Է�: "); fgets(str, sizeof(str), stdin);//gets(str);
		if (strcmp(str, "0") == 0) return;//���ҰŸ� 0

		for (int i = 0; i < cnt; i++)
		{
			if (!strcmp(str, profile[i].name))
			{
				profile[i].is_deleted = 1;
				//strcpy(profile[i].name, "0");//������ �ε����� �迭�� -1 �ֱ�
				break;
			}
			else if (i == cnt - 1)
			{
				printf("�߸��� �Է�\n");
			}
		}
	}

	return;
}

void randomize()
{
	printf("randomize~\n");
}