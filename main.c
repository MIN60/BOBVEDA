#include <stdio.h>
#include <string.h>
#include "struct.h"
#include "main.h"
#include "func.h"

struct PROFILE profile[MAX_NUM]; //���������� ����ü �迭 ����
int cnt;

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
	while ((fscanf(ifp, "%s %c %d %d %d", profile[i].name, &profile[i].gender , &profile[i].ex_team, &profile[i].team, &profile[i].is_deleted)) == 5)
	{
		profile[i].is_deleted = 0;//1�� ����
		i++;
	}

	cnt = i; //���� ��� �� ����

	printf("-----------\n");
	for (int j = 0; j < cnt; j++)
	{
		printf("%s %c %d\n", profile[j].name, profile[j].gender, profile[j].ex_team);
	}
	printf("-----------\n");


	fclose(ifp); //������� ����ü �迭�� input.txt ���� ����

	Search();
	Remove();

	Randomize();

	FILE* ofp;
	ofp = fopen("output.txt", "w");
	if (ofp == NULL)
	{
		printf("there's no output.txt\n");

		return 1;
	}

	//����ü �迭 ofp�� ����
	for (int i = 0; i < cnt; i++)
	{
		if(profile[i].is_deleted==1)
		{
			continue;
		}
		else
		{
			fprintf(ofp, "%s %c %d %d %d\n", profile[i].name, profile[i].gender, profile[i].ex_team, profile[i].team, profile[i].is_deleted);
			/*if (fprintf(ofp, "%s %c %d %d\n", profile[i].name, profile[i].gender, profile[i].ex_team, profile[i].team)< 0)
			{
				printf("%d��° fprintf ����\n", i);
			}	*/		
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