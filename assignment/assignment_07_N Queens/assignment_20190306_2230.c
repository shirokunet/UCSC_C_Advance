/****************************************************
Prologue
University of California Extension, Santa Cruz
Advanced C Programming
Instructor: Rajainder A. Yeldandi
Author: Reyes
Assignment Number: 7
Topic: Queens.
file name: assignment.c
Date: Mar 6, 2019
Objective: Practice.
Comments: None.
Input sample: 
****************************************************/

#include <stdio.h>

#define N 8
#define QUEEN   'Q'
#define BLANK   '.'

int board[N];
int check1[N];
int check2[N * 2 - 1];
int check3[N * 2 - 1];
char board2[8][8];

void initboard(void)
{
    for(int x = 0; x < 8; ++x)
    {
        for(int y = 0; y < 8; ++y)
        {
            board2[x][y] = BLANK;
        }
    }
}

void setqueen(int x, int y)
{
    board2[x][y] = QUEEN;
}

void printboard(void)
{
    printf("\n");
    for(int y = 0; y < 8; ++y)
    {
        printf("%c", board2[0][y]);
        for(int x = 1; x < 8; ++x)
        {
            printf(" %c", board2[x][y]);
        }
        printf("\n");
    }
    printf("\n");
}

void solve(int n)
{
    for (int i = 0; i < N; i++)
    {
        if (check1[i] == 1)
            continue;
        if (check2[i+n] == 1)
            continue;
        if (check3[i-n+N-1] == 1)
            continue;
        board[n] = i;
        if (n == N - 1)
        {
            initboard();
            for (int j = 0; j < N; j++)
            {
                printf("%d ", board[j]);
                setqueen(j, board[j]);
            }
            printf("\n");
            // printboard();
        }
        else
        {
            check1[i] = 1;
            check2[i+n] = 1;
            check3[i-n+N-1] = 1;
            solve(n + 1);
            check1[i] = 0;
            check2[i+n] = 0;
            check3[i-n+N-1] = 0;
        }
    }
}

int main(void)
{
    /* initialize */
    for (int i = 0; i < N; i++) check1[i] = 0;
    for (int i = 0; i < N * 2 - 1; i++)
    {
        check2[i] = 0;
        check3[i] = 0;
    }

    // printf ("Input like below\n");

    solve(0);
    // board[0] = 1;
    // solve(0);

    // initboard();
    // for (int j = 0; j < N; j++)
    // {
    //     // printf("%d ", board[j]);
    //     setqueen(j, board[j]);
    // }

    // printboard();

    return 0;
}