#include <time.h>
#include <stdlib.h>
 
#include "struct.h"
#include "randomize.h"

void InitRandom() {
    srand(time(NULL)); 
}

int RandomNumber(int num) { 
    if (num <= 0) return -1;  
    return rand() % num;
}

int TeamSelect(TEAM* Team, MEMBER* Male, MEMBER* Female, int Mcount, int Fcount) {

    int* FemaleIdx = CreateNumArr(Fcount);
    int* MaleIdx = CreateNumArr(Mcount);

    int LastIndex = 6;
    int idx = 0;

    int RemainingF = Fcount; 
    int RemainingM = Mcount; 

    int SelectedIdx;
    int wcount = 0;
    int mcount = 0;

    for (int i = 0; i < 7; i++) 
    {
        Team[i].count = 0;
    }
     
    for (int i = 0; i < Fcount;) { 
        int attempts = 0;
        int maxAttempts = 50;  

        while (attempts < maxAttempts) {
            int Random_Idx = RandomNumber(RemainingF); 
            SelectedIdx = FemaleIdx[Random_Idx]; 
            int teamIdx = idx % (LastIndex + 1);

            if (!DuplCheck(Female[SelectedIdx].prev_team, Team[teamIdx].set)) { 
                wcount++;
                Team[teamIdx].member[(Team[teamIdx].count)] = Female[SelectedIdx]; 
                Team[teamIdx].set[Team[teamIdx].count] = Female[SelectedIdx].prev_team;  
                Team[teamIdx].count++;
                ArrUpdate(&FemaleIdx, &RemainingF, Random_Idx);  
                idx++;  
                i++;
                break;  
            }

            attempts++;

            if (attempts >= maxAttempts) {
                
                Team[teamIdx].member[(Team[teamIdx].count)] = Female[SelectedIdx];
                Team[teamIdx].set[Team[teamIdx].count] = Female[SelectedIdx].prev_team;
                Team[teamIdx].count++;
                ArrUpdate(&FemaleIdx, &RemainingF, Random_Idx);
                idx++;
                i++;
                break;
            }
        }
    }
     
    for (int i = 0; i < Mcount;) {
        int attempts = 0;
        int maxAttempts = 50; 

        while (attempts < maxAttempts) {
            int Random_Idx = RandomNumber(RemainingM); 
            SelectedIdx = MaleIdx[Random_Idx];  
            int teamIdx = idx % (LastIndex + 1);

            if (!DuplCheck(Male[SelectedIdx].prev_team, Team[teamIdx].set)) {
                 
                mcount++;
                Team[teamIdx].member[(Team[teamIdx].count)] = Male[SelectedIdx]; 
                Team[teamIdx].set[Team[teamIdx].count] = Male[SelectedIdx].prev_team;  
                Team[teamIdx].count++;
                ArrUpdate(&MaleIdx, &RemainingM, Random_Idx);  
                idx++;  
                i++;
                break;  
            }

            attempts++; 
            if (attempts >= maxAttempts) { 
                Team[teamIdx].member[(Team[teamIdx].count)] = Male[SelectedIdx];
                Team[teamIdx].set[Team[teamIdx].count] = Male[SelectedIdx].prev_team;
                Team[teamIdx].count++;
                ArrUpdate(&MaleIdx, &RemainingM, Random_Idx);
                idx++;
                i++;
                break;
            }
        }
    }

    free(FemaleIdx);
    free(MaleIdx);
    return 0;  
}

int* CreateNumArr(int num) {
    int* new_arr = malloc(sizeof(int) * num);
    for (int i = 0; i < num; i++) {
        new_arr[i] = i;
    }
    return new_arr;
}

int DuplCheck(int n, int* arr) 
{ 
    if (n == -1) return 0;  
    else
    {
        for (int i = 0; i < 5; i++)
        {
            if (arr[i] == n)
            {
                return 1; 
            }
        }
        return 0; 
    }
}

void ArrUpdate(int** arr, int* size, int index) {
    if (*size <= 0 || index >= *size) return; 
    int temp = (*arr)[index];
    (*arr)[index] = (*arr)[*size - 1];
    (*arr)[*size - 1] = temp;
     
    (*size)--; 
    if (*size > 0) {
        int* temp_arr = realloc(*arr, (*size) * sizeof(int));
        if (temp_arr == NULL) {
            perror("Memory reallocation failed");
            exit(1);
        }
        *arr = temp_arr;
    }
    else {
        free(*arr);
        *arr = NULL;
    }
}

void Classification(MEMBER* Tptr, MEMBER* Mptr, MEMBER* Fptr, MEMBER* temp, const int size, int* FCount, int* MCount, int* TCount)	 
{ 
    *FCount = 0;  
    *MCount = 0;
    *TCount = 0;

    for (int i = 0; i < size; i++)
    {
        if (Tptr[i].gender == 'F')
        {
            Fptr[*FCount] = Tptr[i];
            ++(*FCount);
        }
        else if (Tptr[i].gender == 'M')
        {
            Mptr[*MCount] = Tptr[i];
            ++(*MCount);
        }
        else if (Tptr[i].gender == ('N' || 'E'))
        {
            temp[*TCount] = Tptr[i];
            ++(*TCount);
        }
    }
}