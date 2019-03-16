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
Input sample :
(18+(17-(16+15))*(14-(13+12)+11))/(10-(9-(8-(7-6))))+(5+(4*(3-2))/1)
****************************************************/

#include <stdio.h>
#include <string.h>

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
    printf("\n");
}

int rpn(struct stack *stk, char pol[])
{
    int value = 0;
    int _1stValue;
    int _2ndValue;

    printf("\n");
    for (int i = 0; pol[i] != '\0'; i++)
    {
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
    printf("\n");

    return pop(stk);
}

void convert_rpn(char str[100], char str_rpn[100])
{
    char varstack[100];
    char porstr[100][20];
    char numstr[20];
    int stack_size = 0;
    int varstacksize = 0;
    int numstrsize = 0;
    int strLen = strlen(str);

    if (strLen==0)
    {
        printf("The sting is NULL.\n");
        return;
    }
    if (strLen>=98)
    {
        printf("The string is too long.\n");
        return;
    }

    // Add '(', ')' to front and end.
    for (int i = strLen; i > 0; i--)
        str[i]=str[i-1];
    str[0]='(';
    strLen+=2;
    str[strLen-1]=')';
    str[strLen]='\0';

    for (int i = 0; i < strLen; i++)
    {
        switch (str[i])
        {
            case '0':case '1':case '2':case '3':case '4':
            case '5':case '6':case '7':case '8':case '9':
            case '.':
                numstr[numstrsize] = str[i];
                numstrsize++;
                break;
            case '+':
            case '-':
                if (numstrsize > 0)
                {
                    numstr[numstrsize] = '\0';
                    strcpy(porstr[stack_size],numstr);
                    stack_size++;
                    numstrsize = 0;
                }
                while (varstacksize > 0)
                {
                    if (varstack[varstacksize-1] == '(')
                        break;
                    // Convert to rpn.
                    porstr[stack_size][0] = varstack[varstacksize-1];
                    porstr[stack_size][1] = '\0';
                    stack_size++;
                    varstacksize--;
                }
                varstack[varstacksize] = str[i];
                varstacksize++;
                break;
            case '*':
            case '/':
                if (numstrsize > 0)
                {
                    numstr[numstrsize] = '\0';
                    strcpy(porstr[stack_size],numstr);
                    stack_size++;
                }
                numstrsize = 0;
                if (varstacksize>0 && (varstack[varstacksize-1]=='*' || varstack[varstacksize-1]=='/'))
                {
                    // Convert to rpn.
                    porstr[stack_size][0] = varstack[varstacksize-1];
                    porstr[stack_size][1] = '\0';
                    stack_size++;
                    varstacksize--;
                }
                varstack[varstacksize] = str[i];
                varstacksize++;
                break;
            case '(':
                varstack[varstacksize] = str[i];
                varstacksize++;
                break;
            case ')':
                if (numstrsize>0)
                {
                    numstr[numstrsize] = '\0';
                    strcpy(porstr[stack_size],numstr);
                    stack_size++;
                }
                numstrsize = 0;
                while (varstacksize>0)
                {
                    if (varstack[varstacksize-1] == '(')
                    {
                        varstacksize--;
                        break;
                    }
                    porstr[stack_size][0] = varstack[varstacksize-1];
                    porstr[stack_size][1] = '\0';
                    stack_size++;
                    varstacksize--;
                }
                break;
        }
    }

    for (int i = 0; i < stack_size; ++i)
    {
        strcat(str_rpn, porstr[i]);
        if (i < stack_size-1)
            strcat(str_rpn, ",");
    }

    return;
}

int main()
{
    char str[100] = "(18+(17-(16+15))*(14-(13+12)+11))/(10-(9-(8-(7-6))))+(5+(4*(3-2))/1)";
    char str_rpn[100] = "";
    struct stack stk;
    init_stack(&stk);

    printf("Formula     : %s\n", str);

    convert_rpn(str, str_rpn);
    printf("Formula_RPN : %s\n", str_rpn);

    printf("Result : %d\n", rpn(&stk, str_rpn));

    int answer = (18+(17-(16+15))*(14-(13+12)+11))/(10-(9-(8-(7-6))))+(5+(4*(3-2))/1);
    printf("Answer : %d\n", answer);

    return 0;
}