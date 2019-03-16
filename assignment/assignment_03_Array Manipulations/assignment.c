/****************************************************
Prologue
University of California Extension, Santa Cruz
Advanced C Programming
Instructor: Rajainder A. Yeldandi
Author: Reyes
Assignment Number: 3
Topic: Array.
file name: assignment.c
Date: Jan 25, 2019
Objective: Practice.
Comments: None.
Input sample: 14,17,56,85,22,97,33,71,19,62,38,44,51,29,77,65,40,99,4,47,67,41,23,81,73,8,100,35,91,58,59,25,15,38,95,60,20,7,50,10
****************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

int main(void)
{
    char str[500];
    char *token;
    int value[100];
    int value_ascending[100];
    int index_total = 0;
    int tmp = 0;
    int find_value = 0;
    int value_subscript[9] = {41,71,5,58,95,22,61,0,47};
    bool found_flag = false;

    printf("Enter a array of value.\n");
    scanf("%s", str);
    for(token=strtok(str, ","); token!=NULL; token=strtok(NULL, ",")) {
        value[index_total] = atoi(token);
        index_total += 1;
    }
    printf("\n");

    printf("Array you enterd.\n");
    for (int i = 0; i < index_total; ++i) {
        printf("%d", value[i]);
        if (i < index_total-1) printf(",");
    }
    printf("\n\n");

    printf("Array sorted in ascending order.\n");
    for (int i = 0; i < index_total; ++i) {
        value_ascending[i] = value[i];
    }
    for (int i=0; i<index_total; ++i) {
        for (int j=i+1; j<index_total; ++j) {
            if (value_ascending[i] > value_ascending[j]) {
                tmp =  value_ascending[i];
                value_ascending[i] = value_ascending[j];
                value_ascending[j] = tmp;
            }
        }
    }
    for (int i = 0; i < index_total; ++i) {
        printf("%d", value_ascending[i]);
        if (i < index_total-1) printf(",");
    }
    printf("\n\n");

    printf("Enter a value. I will show you the index of the value.\n");
    scanf("%d", &find_value);
    for (unsigned int i = 0; i < sizeof(value_subscript) / sizeof(int); ++i) {
        if (find_value == value_subscript[i]){
            for (int j = 0; j < index_total; ++j) {
                if (find_value == value[j]) {
                    printf("The index is %d\n", j);
                    found_flag = true;
                }
            }
        }
    }
    if (found_flag == false) printf("Could not find the value.\n");
    printf("\n");

    return 0;
}
