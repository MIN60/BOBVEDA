#pragma once

#include "main.h"

struct PROFILE
{
	char name[NAME_LEN];
	char gender;
	int ex_team;
	int team;
	int is_deleted;//1: ªË¡¶µ 
};

extern struct PROFILE profile[MAX_NUM];
extern struct PROFILE final_profile[MAX_NUM];