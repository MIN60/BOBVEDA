#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#include "randomize.h"
#include "struct.h"
#include "file.h"
#include "absent.h"


int main(int argc, char* argv[]) {
    if (argc < 4) {
        printf("����: ./group_maker input.txt excludeList output.txt\n");
        return 1;
    }

    const char* input_file = argv[1];
    const char* exclude_list = argv[2];
    const char* output_file = argv[3];

    printf("�Է� ����: %s\n", input_file);
    printf("���� ���: %s\n", exclude_list);
    printf("��� ����: %s\n", output_file);

    MEMBER member[30]; // ��ü ���
    MEMBER absent[256]; // ���ܵ� ���
    MEMBER Male[30], Female[30], Temp[30]; // ���� �з�
    int Mcount, Fcount, Tcount;

    // �Է� ���� �б�
    ReadOrigin(member, input_file);

    // �о�� ��� ���
    printf("\n�о�� ��ü ��� ���:\n");
    for (int i = 0; i < 30; i++) {
        if (member[i].name[0] != '\0') {  // ������� ���� �׸� ���
            printf("%d: %s (%c)\n", i + 1, member[i].name, member[i].gender);
        }
    }

    // ������ ó��
    char ab_copy[256];
    strncpy(ab_copy, exclude_list, sizeof(ab_copy));
    ab_copy[sizeof(ab_copy) - 1] = '\0';
    printf("\n������ ó�� ����...\n");
    int ab_num = Absent(member, ab_copy);
    printf("������ ó�� �Ϸ�. ���ܵ� �ο�: %d��\n", ab_num);

    // ���� �з�
    Classification(member, Male, Female, Temp, 30, &Fcount, &Mcount, &Tcount);
    // ���� �з� Ȯ��
    PrintMembers(Male, Female, Temp, Mcount, Fcount, Tcount);
    printf("���ܵ� �ο� ��: %d\n", Tcount);
    if (Tcount != ab_num) {
        printf("���: ���� �ο� �� ����ġ (ab_num=%d, Tcount=%d)\n", ab_num, Tcount);
    }

    // �Ἦ�� ���� ��ȯ
    Genderchange(Temp, ab_num);

    // �� �� ���
    int total_members = Mcount + Fcount;
    int members_per_team = 4; // �⺻ ���� �ο���
    int team_count = (total_members + members_per_team - 1) / members_per_team; // �ø� ���

    // ���� �ο��� �ʹ� ������ 3������ ����
    if (total_members / team_count < 3) {
        members_per_team = 3;
        team_count = (total_members + members_per_team - 1) / members_per_team;
    }

    printf("\n�� ���� ����:\n");
    printf("�� �ο�: %d�� (��:%d, ��:%d)\n", total_members, Mcount, Fcount);
    printf("�� ��: %d, ���� �ο�: �� %d��\n", team_count, members_per_team);

    // �� ����
    TEAM* teams = (TEAM*)malloc(sizeof(TEAM) * team_count);
    for (int i = 0; i < team_count; i++) {
        teams[i].member = (MEMBER*)malloc(sizeof(MEMBER) * (members_per_team + 1)); // �߰� �ο� ���ɼ�
        if (!teams[i].member) {
            perror("Memory allocation failed");
            exit(1);
        }
        teams[i].count = 0;
        for (int j = 0; j < 10; j++) { // ����� ū size�� �ʱ�ȭ
            teams[i].set[j] = -1;
        }
    }

    // �� ����
    InitRandom();
    TeamSelect(teams, Male, Female, Mcount, Fcount, team_count);

    // ��� ���� ����
    WriteText(teams, Temp, Tcount, team_count, output_file);

    // �޸� ����
    for (int i = 0; i < team_count; i++) {
        free(teams[i].member);
    }
    free(teams);

    return 0;
}