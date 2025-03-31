#ifndef _STRUCT_H_
#define _STRUCT_H_

typedef struct MEMBER MEMBER;
typedef struct TEAM TEAM;

struct MEMBER {
    char name[20];
    int prev_team;
    char gender;
};

struct TEAM {
    MEMBER* member;  
    int set[5];  
    int count;  
};

#endif