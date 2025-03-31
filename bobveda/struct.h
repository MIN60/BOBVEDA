#ifndef _STRUCT_H_
#define _STRUCT_H_

typedef struct MEMBER MEMBER;
typedef struct TEAM TEAM;


struct MEMBER {
    char name[20];
    int prev_team; // ���� ���� ������ ��� -1�� �ʱ�ȭ
    char gender; // f:female, m:male
};

struct TEAM {
    MEMBER* member; //member �߰��� �迭
    int set[5]; //�ߺ� checking�� �迭 -1�� �ʱ�ȭ
    int count; //��� ��, TeamSelect�Լ� ������ 0���� �ʱ�ȭ
};


#endif