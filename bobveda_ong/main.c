#include <stdio.h>
#include <string.h>
#include "struct.h"
#include "main.h"
#include "func.h"

struct PROFILE profile[MAX_NUM]; //���������� ����ü �迭 ����

int main()
{
	FILE* ifp;
	ifp = fopen("input.txt", "r");
	if (ifp == NULL)
	{
		printf("there's no input.txt\n");
		//perror(ifp);
		return 1;
	}

	int i = 0;
	while ((fscanf(ifp, "%s %c %d %d", profile[i].name, &profile[i].gender , &profile[i].ex_team, &profile[i].team)) == 4)
	{
		profile[i].is_deleted = 0;//1�� ����
		i++;
	}

	cnt = i; //���� ��� �� ����

	fclose(ifp); //������� ����ü �迭�� input.txt ���� ����

	Search();
	Remove();

	Randomize();

	FILE* ofp;
	ofp = fopen("output.txt", "w");
	if (ofp == NULL)
	{
		printf("there's no output.txt\n");
		//perror(ofp);
		return 1;
	}

	//����ü �迭 ofp�� ����(-1�� ���� �� ����)
	for (int i = 0; i < cnt; i++)
	{
		if(profile[i].is_deleted==1)//if (!strcmp(profile[i].name, "0"))//���� name�� 0�� ����ִ� ���̶��
		{
			continue;
		}
		else
		{
			if (fprintf(ofp, "%s %c %d %d", profile[i].name, profile[i].gender, profile[i].ex_team, profile[i].team)< 0)
			{
				printf("%d��° fprintf ����\n", i);
			}			
		}
		//if (fprintf(ofp, "%s %c %d %d", profile[i].name, &profile[i].gender, &profile[i].ex_team, &profile[i].team)< 0)
		//{
		//	printf("%d��° fprintf ����\n", i);
		//}
		//else
		//{
		//	if ((strcmp(profile[i].name, "0") != 0)
		//	{
		//		
		//	}
		//}
	}

	fclose(ofp);

	return 0;
}