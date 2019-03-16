/****************************************************
Prologue
University of California Extension, Santa Cruz
Advanced C Programming
Instructor: Rajainder A. Yeldandi
Author: Reyes
Assignment Number: 10
Topic: Hanoi towers.
file name: assignment.c
Date: Feb 16, 2019
Objective: Practice.
Comments: None.
Input sample: 
****************************************************/

#include<stdio.h>

#define DISK_N 4

void show_towers(int towers[3][DISK_N])
{
    for (int j = 0; j < DISK_N; ++j)
    {
        printf(" ");
        for (int i = 0; i < 3; ++i)
        {
            printf("%d\t", towers[i][j]);
        }
        printf("\n");
    }
    printf(" -\t-\t-\n");
    printf(" A\tB\tC\n\n");
}

void move_towers(int target_disk, char *from, char *dest, int towers[3][DISK_N])
{
    int from_number = 0;
    int dest_number = 0;

    if (*from=='A') from_number = 0;
    else if (*from=='B') from_number = 1;
    else if (*from=='C') from_number = 2;

    if (*dest=='A') dest_number = 0;
    else if (*dest=='B') dest_number = 1;
    else if (*dest=='C') dest_number = 2;

    /* search in the from tower */
    for (int j = DISK_N-1; j >=0 ; --j)
    {
        if (towers[from_number][j] == target_disk){
            towers[from_number][j] = 0;
            break;
        }
    }

    /* search in the dest tower */
    for (int j = DISK_N-1; j >=0 ; --j)
    {
        if (towers[dest_number][j] == 0){
            towers[dest_number][j] = target_disk;
            break;
        }
    }
}

void Hanoi(int n, char *from, char *work, char *dest, int towers[3][DISK_N])
{
    if(n>=2) Hanoi(n-1, from, dest, work, towers);

    printf("Move disk %d from %s to %s.\n", n, from, dest);
    move_towers(n, from, dest, towers);
    show_towers(towers);

    if(n>=2) Hanoi(n-1, work, from, dest, towers);
}

int main()
{
    int towers[3][DISK_N];

    /* init value */
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < DISK_N; ++j)
        {
            if (i==0) towers[i][j] = j+1;
            else towers[i][j] = 0;
        }
    }
    printf("Initial position.\n");
    show_towers(towers);

    Hanoi(DISK_N,"A","B","C", towers);

    return 0;
}