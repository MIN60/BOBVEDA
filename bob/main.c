#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "struct.h"
#include "file.h"



int main()
{
	MEMBER member[30];
	ReadOrigin(member, "origin.txt");
	//WriteText(TEAM * Wptr, const char* file_name);

	return 0;
}