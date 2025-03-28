#ifndef _ONG_STRUCT_H_
#define _ONG_STRUCT_H_

typedef struct MEMBER MEMBER;
typedef struct TEAM TEAM;

struct MEMBER {
    char name[20];
    int prev_team;
    char gender;
};

struct TEAM {
    MEMBER* member; //member 추가할 배열
    int set[5]; //중복 checking할 배열 -1로 초기화
    int count; //멤버 수, TeamSelect함수 내에서 0으로 초기화
};

#endif