/****************************************************
Prologue
University of California Extension, Santa Cruz
Advanced C Programming
Instructor: Rajainder A. Yeldandi
Author: Reyes
Assignment Number: 1
Topic: TEMPERATURE CONVERSION
file name: assignment.c
Date: Jan 18, 2019
Objective: Practice.
Comments: None.
****************************************************/

#include <stdio.h>

int main(void)
{
    printf ("Input like below\n");
    printf ("152 deg. F, 99 deg. C\n");
 
    int deg_f = 0;
    int deg_c = 0;
    scanf("%d deg. F, %d deg. C", &deg_f, &deg_c);
    printf("You input:%d deg. F, %d deg. C\n", deg_f, deg_c);

    // From F to C ==> C = (F temp - 32) * 5 / 9
    int deg_f2c = (deg_f - 32) * 5 / 9;
    printf("From F to C: %d deg. C\n", deg_f2c);

    // From C to F ==> F = (C temp * 9 / 5) + 32
    int deg_c2f = (deg_c * 9 / 5) + 32;
    printf("From C to F: %d deg. F\n", deg_c2f);

    return 0;
}