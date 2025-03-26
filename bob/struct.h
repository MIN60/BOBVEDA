#ifndef _STRUCT_H_
#define _STRUCT_H_

typedef struct MEMBER MEMBER;
typedef struct TEAM TEAM;

struct MEMBER
{
	char name[20];
	int prev_team; //���� ���� ������ ��� -1�� ����
	char gender; //f:female, m:male
};

struct TEAM
{
	//TEAM ��ȣ�� +1�ؼ� ���
	MEMBER *member; //member �߰��� �迭
	int set[5]; //�ߺ� checking�� �迭
	int count;//���� �� �ο�
};

#endif //!_STRUCT_H_