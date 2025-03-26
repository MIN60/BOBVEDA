#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//0 ~ num-1 사이의 난수 출력
void InitRandom()
{
    srand(time(NULL)); // 프로그램 시작 시 한 번만 실행
}

int RandomNumber(int num)
{
    if (num <= 0) return -1; // 안전 장치
    return rand() % num;
}

//숫자 구성 배열 생성
int* CreateNumArr(int num)
{
	int* new_arr = malloc(sizeof(int) * num);
	for (int i = 0; i < num; i++)
	{
		new_arr[i] = i;
	}
	return new_arr;
}

void ArrUpdate(int** arr, int size, int index) {
    if (size <= 1 || index >= size) return;

    int temp = (*arr)[index];
    (*arr)[index] = (*arr)[size - 1];
    (*arr)[size - 1] = temp;

    size -= 1;

    if (size > 0) {
        *arr = realloc(*arr, size * sizeof(int));
        if (*arr == NULL) {
            perror("Memory reallocation failed");
            exit(1);
        }
    } else {//size가 0일 때 예외처리
        free(*arr);
        *arr = NULL;
    }
}
