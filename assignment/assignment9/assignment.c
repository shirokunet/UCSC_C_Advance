/****************************************************
Prologue
University of California Extension, Santa Cruz
Advanced C Programming
Instructor: Rajainder A. Yeldandi
Author: Reyes
Assignment Number: 9
Topic: Queues.
file name: assignment.c
Date: Feb 24, 2019
Objective: Practice.
Comments: None.
Input sample: 
****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DATA 32

struct queue
{
    int arr[MAX_DATA];
    int last;
};

int enq(struct queue *que, int input)
{
    if (que->arr[que->last] <= MAX_DATA)
    {
        que->arr[que->last] = input;
        que->last++;

        return 0;
    }
    else
    {
        printf("Could not add data anymore.\n");
        return -1;
    }
}

int deq(struct queue *que)
{
    int output = que->arr[0];

    if (output != 0)
    {
        for (int i = 0; i < MAX_DATA-1; ++i) que->arr[i] = que->arr[i+1];
        que->last--;
        return output;
    }
    else
    {
        printf("Could not find data.\n");
        return -1;
    }
}

void init_queue(struct queue *que)
{
    for (int i = 0; i < MAX_DATA; i++) que->arr[i] = 0;
    que->last = 0;
}

void show_queue(struct queue *que)
{
    for (int i = 0; i < MAX_DATA; i++) 
    {
        if (i >= que->last)
            break;
        printf("%d ", que->arr[i]);
    }
    printf("\n\n");
}

int main()
{
    FILE *lf;
    char bff[100];
    char *value_a;
    int value_num;
    struct queue que;
    init_queue(&que);

    /* file open */
    if (!(lf=fopen("input.csv","r")))
    {
        printf("File open error.\n");
        return -1;
    }

    for (int i = 0 ; i < MAX_DATA ; i++)
    {
        /* read data */
        fgets(bff, 100, lf);
        value_num = 0;
        value_a = strtok(bff, ",");
        value_num = atoi(strtok(NULL, ","));
        printf("%s,%d: ", value_a, value_num);

        if (*value_a == 'E')
            enq(&que, value_num);
        else if (*value_a == 'D')
            deq(&que);

        show_queue(&que);
    }

    return 0;
}