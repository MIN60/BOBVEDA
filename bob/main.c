#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "struct.h"
#include "readwrite.h"



int main()
{
	MEMBER member[30];
	ReadOrigin(member, "origin.txt");
	//ReadPrev(MEMBER * Rptr, const char* file_name);
	//WriteText(TEAM * Wptr, const char* file_name);

	return 0;
}