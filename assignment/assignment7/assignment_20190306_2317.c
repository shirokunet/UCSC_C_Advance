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

#define BOARD_N 8
#define QUEEN 'Q'
#define BLANK '.'
#define TRUE   1
#define FALSE  0

int answercount = 0;
char board[BOARD_N][BOARD_N];

void initboard()
{
    for(int x=0; x<BOARD_N; ++x)
    {
        for(int y=0; y<BOARD_N; ++y)
        {
            board[x][y] = BLANK;
        }
    }
}

void printboard(char b[BOARD_N][BOARD_N])
{
    for(int y=0; y<BOARD_N; ++y)
    {
        for(int x=0; x<BOARD_N; ++x)
        {
            printf(" %c", b[x][y]);
        }
        printf("\n");
    }
    printf("\n");
}

void copyboard(char dest[BOARD_N][BOARD_N], char src[BOARD_N][BOARD_N])
{
    for(int x=0; x<BOARD_N; ++x)
    {
        for(int y=0; y<BOARD_N; ++y)
        {
            dest[x][y] = src[x][y];
        }
    }
}

void rotate(char dest[BOARD_N][BOARD_N], char src[BOARD_N][BOARD_N])
{
    char work[BOARD_N][BOARD_N];

    for(int x=0; x<BOARD_N; ++x)
    {
        for(int y=0; y<BOARD_N; ++y)
        {
            work[y][BOARD_N-1-x] = src[x][y];
        }
    }

    copyboard(dest, work);
}

void lrmirror(char dest[BOARD_N][BOARD_N], char src[BOARD_N][BOARD_N])
{
    char work[BOARD_N][BOARD_N];

    for(int x=0; x<BOARD_N; ++x)
    {
        for(int y=0; y<BOARD_N; ++y)
        {
            work[BOARD_N-1-x][y] = src[x][y];
        }
    }

    copyboard(dest, work);
}

int compareboard(char b0[BOARD_N][BOARD_N], char b1[BOARD_N][BOARD_N])
{
    // for(int x=0; x<BOARD_N; ++x)
    // {
    //     for(int y=0; y<BOARD_N; ++y)
    //     {
    //         if(b0[x][y] == b1[x][y])
    //              continue;
    //         return (b0[x][y] == QUEEN) ? -1 : 1;
    //     }
    // }
    // return 0;
    for(int x=0; x<BOARD_N; ++x)
    {
        for(int y=0; y<BOARD_N; ++y)
        {
            if(b0[x][y] != b1[x][y])
                return 0;
        }
    }
    return 1;
}

int isunique()
{
    char work[BOARD_N][BOARD_N];

    copyboard(work, board);
    // printboard(work);

    rotate(work, work);
    // printboard(work);
    if(compareboard(board, work) > 0)
        return  FALSE;

    rotate(work, work);
    if(compareboard(board, work) > 0)
        return  FALSE;

    rotate(work, work);
    if(compareboard(board, work) > 0)
        return  FALSE;

    lrmirror(work, board);
    if(compareboard(board, work) > 0)
        return  FALSE;

    rotate(work, work);
    if(compareboard(board, work) > 0)
        return  FALSE;

    rotate(work, work);
    if(compareboard(board, work) > 0)
        return  FALSE;

    rotate(work, work);
    if(compareboard(board, work) > 0)
        return  FALSE;

    return  TRUE;
}

void setqueen(int x, int y)
{
    board[x][y] = QUEEN;
}

void setblank(int x, int y)
{
    board[x][y] = BLANK;
}

int ison(int x, int y)
{
    if(x<0 || x>=BOARD_N)
        return  FALSE;
    if(y<0 || y>=BOARD_N)
        return  FALSE;

    return  TRUE;
}

int isokleft(int x, int y)
{
    int stat = TRUE;

    for(;;)
    {
        --x;
        if(! ison(x, y))
            break;

        if(board[x][y] == QUEEN)
        {
            stat = FALSE;
            break;
        }
    }

    return stat;
}

int isokleftup(int x, int y)
{
    int stat = TRUE;

    for(;;)
    {
        --x;
        --y;
        if(! ison(x, y))
            break;

        if(board[x][y] == QUEEN)
        {
            stat = FALSE;
            break;
        }
    }

    return stat;
}

int isokleftdown(int x, int y)
{
    int stat = TRUE;

    for(;;)
    {
        --x;
        ++y;
        if(! ison(x, y))
            break;

        if(board[x][y] == QUEEN)
        {
            stat = FALSE;
            break;
        }
    }

    return stat;
}

int isok(int x, int y)
{
    if(! isokleft(x, y))
        return  FALSE;

    if(! isokleftup(x, y))
        return  FALSE;

    if(! isokleftdown(x, y))
        return  FALSE;

    return  TRUE;
}

void foundanswer(void)
{
    if(! isunique())
        return;

    ++answercount;
    printf("Answer %d\n", answercount);

    printboard(board);
}

void tryqueen(int x, int y)
{
    if(! isok(x, y))
        return;

    setqueen(x, y);

    if(x == BOARD_N-1)
    {
        foundanswer();
    }
    else
    {
        for(int z=0; z<BOARD_N; ++z)
        {
            tryqueen(x+1, z);
        }
    }

    setblank(x, y);
}

int main()
{
    int position = 0;

    printf ("Input a first queen position: "); 
    scanf("%d", &position);
    printf("\n");

    initboard();
    setqueen(0, position);
    for(int y=1; y<BOARD_N; ++y) {
        tryqueen(1, y);
    }

    return 0;
}
