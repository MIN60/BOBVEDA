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
    MEMBER* member; //member �߰��� �迭
    int set[5]; //�ߺ� checking�� �迭 -1�� �ʱ�ȭ
    int count; //��� ��, TeamSelect�Լ� ������ 0���� �ʱ�ȭ
};

#endif