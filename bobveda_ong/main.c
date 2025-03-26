#include <stdio.h>
#include <string.h>
#include "struct.h"
#include "main.h"
#include "func.h"

struct PROFILE profile[MAX_NUM]; //전역변수로 구조체 배열 선언

int main()
{
	FILE* ifp;
	ifp = fopen("input.txt", "r");
	if (ifp == NULL)
	{
		printf("there's no input.txt\n");
		perror(ifp);
		return 1;
	}

	int i = 0;
	while ((fscanf(ifp, "%s %c %d %d", profile[i].name, &profile[i].gender , &profile[i].ex_team, &profile[i].team)) == 4)
	{
		profile[i].is_deleted = 0;//1이 삭제
		i++;
	}

	cnt = i; //실제 사람 수 저장

	fclose(ifp); //여기까지 구조체 배열에 input.txt 내용 넣음

	search();
	remove();

	randomize();

	FILE* ofp;
	ofp = fopen("output.txt", "w");
	if (ofp == NULL)
	{
		printf("there's no output.txt\n");
		perror(ofp);
		return 1;
	}

	//구조체 배열 ofp에 쓰기(-1로 적힌 건 제외)
	for (int i = 0; i < cnt; i++)
	{
		if (!strcmp(profile[i].name, "0"))//만약 name에 0이 들어있는 행이라면
		{
			continue;
		}
		else
		{
			if (fprintf(ofp, "%s %c %d %d", profile[i].name, profile[i].gender, profile[i].ex_team, profile[i].team)< 0)
			{
				printf("%d번째 fprintf 실패\n", i);
			}			
		}
		//if (fprintf(ofp, "%s %c %d %d", profile[i].name, &profile[i].gender, &profile[i].ex_team, &profile[i].team)< 0)
		//{
		//	printf("%d번째 fprintf 실패\n", i);
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