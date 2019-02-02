/****************************************************
Prologue
University of California Extension, Santa Cruz
Advanced C Programming
Instructor: Rajainder A. Yeldandi
Author: Reyes
Assignment Number: 5
Topic: Understanding pointers and address.
file name: assignment.c
Date: Feb 1, 2019
Objective: Practice.
Comments: None.
Input sample: 
****************************************************/

#include <stdio.h>
 
int main()
{
    int i = 25;
    int *i_add;
    int **i_add_pot;

    float f = 3.142;
    float *f_add;
    float **f_add_pot;

    double d = 1.73217;
    double *d_add;
    double **d_add_pot;

    char c = 'x';
    char *c_add;
    char **c_add_pot;

    char s[20] = "Hello, C Programmer";
    char *s_add;
    char **s_add_pot;

    i_add = &i;
    i_add_pot = &i_add;
    printf("Integer: %d\n", i);
    printf("address %p, address of pointer %p\n", i_add, i_add_pot);
    printf("\n");

    f_add = &f;
    f_add_pot = &f_add;
    printf("Float: %f\n", f);
    printf("address %p, address of pointer %p\n", f_add, f_add_pot);
    printf("\n");

    d_add = &d;
    d_add_pot = &d_add;
    printf("Double: %f\n", d);
    printf("address %p, address of pointer %p\n", d_add, d_add_pot);
    printf("\n");

    c_add = &c;
    c_add_pot = &c_add;
    printf("Char: %c\n", c);
    printf("address %p, address of pointer %p\n", c_add, c_add_pot);
    printf("\n");

    s_add = &s[0];
    s_add_pot = &s_add;
    printf("String: %s\n", s);
    printf("address %p, address of pointer %p\n", s_add, s_add_pot);
    printf("\n");

    return 0;
}