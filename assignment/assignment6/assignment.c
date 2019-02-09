/****************************************************
Prologue
University of California Extension, Santa Cruz
Advanced C Programming
Instructor: Rajainder A. Yeldandi
Author: Reyes
Assignment Number: 6
Topic: Tic Tac Toe.
file name: assignment.c
Date: Feb 10, 2019
Objective: Practice.
Comments: None.
Input sample: 
****************************************************/

#include <stdio.h>
#include <stdbool.h>
 

#define BOAD_N 4

void show_status(char array[BOAD_N][BOAD_N]){
    printf("  ");
    for (int i = 0; i < BOAD_N; ++i)
        printf("%d ", i);
    printf("\n");

    for (int i = 0; i < BOAD_N; ++i)
    {
        printf("%d ", i);
        for (int j = 0; j < BOAD_N; ++j)
        {
            printf("%c ", array[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

bool get_player_input(int turn_number, char array[BOAD_N][BOAD_N], int *row, int *column){
    if (turn_number%2 == 0)
        printf("For Player 1 'X'. Input your row and column like 0,0: ");
    else
        printf("For Player 2 'O'. Input your row and column like 0,0: ");

    scanf("%d,%d", row, column);

    /* input error */
    if (*row >= BOAD_N || *column >= BOAD_N)
    {
        printf("Please input under %d.\n\n", BOAD_N);
        return false;
    }
    else if (array[*row][*column] != '-')
    {
        printf("Please input unused area.\n\n");
        return false;
    }

    if (turn_number%2 == 0)
        array[*row][*column] = 'X';
    else
        array[*row][*column] = 'O';

    return true;
}

bool check_game_result(char array[BOAD_N][BOAD_N]){
    int score_player_1_r = 0;
    int score_player_2_r = 0;
    int score_player_1_c = 0;
    int score_player_2_c = 0;
    int score_player_1_x = 0;
    int score_player_2_x = 0;
    int score_player_1_xr = 0;
    int score_player_2_xr = 0;

    for (int i = 0; i < BOAD_N; ++i)
    {
        /* score counter cross */
        if (array[i][i] == 'X')
        {
            score_player_1_x += 1;
        }
        else if (array[i][i] == 'O')
        {
            score_player_2_x += 1;
        }

        /* score counter cross reverse */
        if (array[i][BOAD_N - i - 1] == 'X')
        {
            score_player_1_xr += 1;
        }
        else if (array[i][BOAD_N - i - 1] == 'O')
        {
            score_player_2_xr += 1;
        }

        /* score break */
        if (score_player_1_x == BOAD_N || score_player_1_xr == BOAD_N)
        {
            printf("Player 1 win!\n");
            return true;
        }
        else if (score_player_2_x == BOAD_N || score_player_2_xr == BOAD_N)
        {
            printf("Player 2 win!\n");
            return true;
        }
    }

    for (int i = 0; i < BOAD_N; ++i)
    {
        for (int j = 0; j < BOAD_N; ++j)
        {
            /* score counter row */
            if (array[i][j] == 'X')
            {
                score_player_1_r += 1;
            }
            else if (array[i][j] == 'O')
            {
                score_player_2_r += 1;
            }

            /* score counter column */
            if (array[j][i] == 'X')
            {
                score_player_1_c += 1;
            }
            else if (array[j][i] == 'O')
            {
                score_player_2_c += 1;
            }

            /* score break */
            if (score_player_1_r == BOAD_N || score_player_1_c == BOAD_N)
            {
                printf("Player 1 win!\n");
                return true;
            }
            else if (score_player_2_r == BOAD_N || score_player_2_c == BOAD_N)
            {
                printf("Player 2 win!\n");
                return true;
            }
        }
        score_player_1_r = 0;
        score_player_2_r = 0;
        score_player_1_c = 0;
        score_player_2_c = 0;
    }
    return false;
}

int main()
{
    char array[BOAD_N][BOAD_N];
    int row = 0;
    int column = 0;
    bool input_flag = false;

    /* init value */
    for (int i = 0; i < BOAD_N; ++i)
    {
        for (int j = 0; j < BOAD_N; ++j)
        {
            array[i][j] = '-';
        }
    }
    show_status(array);

    /* game cycle */
    for (int i = 0; i < BOAD_N * BOAD_N; ++i)
    {
        input_flag = false;
        while (input_flag == false)
            input_flag = get_player_input(i, array, &row, &column);

        show_status(array);

        if (check_game_result(array))
            break;

        if (i == BOAD_N * BOAD_N - 1)
            printf("Draw this game.\n");
    }

    return 0;
}