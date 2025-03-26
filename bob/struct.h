#ifndef _STRUCT_H_
#define _STRUCT_H_

typedef struct MEMBER MEMBER;
typedef struct TEAM TEAM;

struct MEMBER
{
	char name[20];
	int prev_team; //직전 조가 없었던 경우 -1로 취함
	char gender; //f:female, m:male
};

struct TEAM
{
	//TEAM 번호는 +1해서 출력
	MEMBER *member; //member 추가할 배열
	int set[5]; //중복 checking할 배열
	int count;//현재 팀 인원
};

#endif //!_STRUCT_H_