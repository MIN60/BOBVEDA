#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

unsigned int next = 1;

typedef struct MEMBER
{
    char name[5];
    char gender;
    unsigned int prev_team;
    unsigned char id;


} MEMBER;

int my_rand()
{
    next = next * 1103515245 + 1234;
    next = (unsigned int)(next / 65536) % 32768;

    return (int)next;
}

void my_srand(unsigned int seed)
{
    next = seed;
}

void shuffle(int* arr, int size)
{
    for (int i = size - 1; i > 0; --i)
    {
        int j = my_rand() % (i + 1);
        int temp = arr[i];

        arr[i] = arr[j];
        arr[j] = temp;
    }
}
