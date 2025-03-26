#pragma once

#include "main.h"

struct PROFILE
{
	char name[NAME_LEN];
	char gender;
	int ex_team = -1;
	int team = -1;
};

extern struct PROFILE profile[MAX_NUM];
extern struct PROFILE final_profile[MAX_NUM];