/****************************************************
Prologue
University of California Extension, Santa Cruz
Advanced C Programming
Instructor: Rajainder A. Yeldandi
Author: Reyes
Assignment Number: 8
Topic: Stacks.
file name: assignment.c
Date: Feb 24, 2019
Objective: Practice.
Comments: None.
Input sample (Reverse Polish Notation):
18,17,16,15,+,-,14,13,12,+,-,11,+,*,+,10,9,8,7,6,-,-,-,-,/,5,4,3,2,-,*,1,/,+,+
****************************************************/

#include <stdio.h>

#define MAX_DATA 32

struct stack
{
    int arr[MAX_DATA];
    int top;
};

int push(struct stack *stk, int input)
{
    if (stk->top <= MAX_DATA)
    {
        stk->arr[stk->top] = input;
        stk->top++;
        return 0;
    }
    else
    {
        printf("Could not add data anymore.\n");
        return -1;
    }
}

int pop(struct stack *stk)
{
    if (stk->top != 0)
    {
        int temp = stk->arr[stk->top-1];
        stk->arr[stk->top-1] = 0;
        stk->top--;
        return temp;
    }
    else
    {
        printf("Could not find data.\n");
        return -1;
    }
}

void init_stack(struct stack *stk)
{
    for (int i = 0; i < MAX_DATA; i++) stk->arr[i] = 0;
    stk->top = 0;
}

void show_stack(struct stack *stk)
{
    for (int i = 0; i < MAX_DATA; i++) 
    {
        if (i >= stk->top)
            break;
        printf("%d ", stk->arr[i]);
    }
    printf("\n\n");
}

int rpn(struct stack *stk, char pol[])
{
    int value = 0;
    int _1stValue;
    int _2ndValue;

    for (int i = 0; pol[i] != '\0'; i++) {
        if ( '1' <= pol[i] && pol[i] <= '9' )
        {
            while (pol[i]!=',') { 
                value = (value * 10)+(pol[i]-'0');
                i++;
            }
            printf("%d: ", value);
            push(stk, value);
            value = 0;
            show_stack(stk);
        }
        else if (pol[i] != ',')
        {
            printf("%c: ", pol[i]);
            _2ndValue = pop(stk);
            _1stValue = pop(stk);
            if (pol[i] == '+') push(stk, _1stValue + _2ndValue);
            else if (pol[i] == '-') push(stk, _1stValue - _2ndValue);
            else if (pol[i] == '*') push(stk, _1stValue * _2ndValue);
            else if (pol[i] == '/') push(stk, _1stValue / _2ndValue);
            show_stack(stk);
        }
    }

    return pop(stk);
}

int main()
{
    struct stack stk;
    init_stack(&stk);

    char pol[100] = "18,17,16,15,+,-,14,13,12,+,-,11,+,*,+,10,9,8,7,6,-,-,-,-,/,5,4,3,2,-,*,1,/,+,+";
    printf("Result : %d\n", rpn(&stk, pol));

    int answer = (18 + (17 - (16 + 15) ) * (14 - (13 + 12) + 11)) / (10 - (9 - (8 - (7 - 6)))) + (5 + (4 * (3 - 2)) / 1);
    printf("Answer : %d\n", answer);

    return 0;
}