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

// 해당 인덱스의 값을 배열 마지막으로 이동한 후 크기 축소
void ArrUpdate(int** arr, int size, int index) {
    if (size <= 1 || index >= size) return; // 배열 크기가 1 이하이거나 잘못된 인덱스라면 리턴

    // 선택된 인덱스 값을 마지막 위치로 이동
    int temp = (*arr)[index];
    (*arr)[index] = (*arr)[size - 1];
    (*arr)[size - 1] = temp;

    // 크기를 1 줄이기 위해 realloc
    size -= 1;
    *arr = realloc(*arr, (size) * sizeof(int));

    if (*arr == NULL && size > 0) {
        perror("Memory reallocation failed");
        exit(1);
    }
}