#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//0 ~ num-1 ������ ���� ���
int RandomNumber(int num)
{
	srand(time(NULL)); // ���� �ʱ�ȭ
	int random = rand() % num;
	
	return random;
}
// FemaleIdx[RandomNumber(Fcount)]
// �迭 ����

int* CreateNumArr(int num)
{
	int* new_arr = malloc(sizeof(int) * num);
	for (int i = 0; i < num; i++)
	{
		new_arr[i] = i;
	}
	return new_arr;
}

// �ش� �ε����� ���� �迭 ���������� �̵��� �� ũ�� ���
void ArrUpdate(int** arr, int size, int index) {
    if (size <= 1 || index >= size) return; // �迭 ũ�Ⱑ 1 �����̰ų� �߸��� �ε������ ����

    // ���õ� �ε��� ���� ������ ��ġ�� �̵�
    int temp = (*arr)[index];
    (*arr)[index] = (*arr)[size - 1];
    (*arr)[size - 1] = temp;

    // ũ�⸦ 1 ���̱� ���� realloc
    size -= 1;
    *arr = realloc(*arr, (size) * sizeof(int));

    if (*arr == NULL && size > 0) {
        perror("Memory reallocation failed");
        exit(1);
    }
}