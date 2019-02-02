/****************************************************
Prologue
University of California Extension, Santa Cruz
Advanced C Programming
Instructor: Rajainder A. Yeldandi
Author: Reyes
Assignment Number: 2
Topic: Calculate min, max and avg.
file name: assignment.c
Date: Jan 18, 2019
Objective: Practice.
Comments: None.
****************************************************/

#include <stdio.h>

int main(void)
{
    int min = 0;
    int max = 0;

    int num = 0;
    int total = 0;
    int avg = 0;

    while (1)
    {
        int value = 0;
        printf("Enter a value or type Ctrl + C to end this program.\n");
        scanf("%d", &value);
        printf("You enterd: %d\n", value);

        if (min == 0 || min > value)
            min = value;
        if (max == 0 || max < value)
            max = value;
        if (avg == 0)
            avg = value;

        num += 1;
        total += value;
        avg = total / num;

        printf("Minimum: %d\n", min);
        printf("Maximum: %d\n", max);
        printf("Average: %d\n", avg);
        printf("\n");
    }

    return 0;
}