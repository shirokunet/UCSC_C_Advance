/****************************************************
Prologue
University of California Extension, Santa Cruz
Advanced C Programming
Instructor: Rajainder A. Yeldandi
Author: Reyes
Assignment Number: 12
Topic: Sort algorithms.
file name: assignment.c
Date: Feb 16, 2019
Objective: Practice.
Comments: None.
Input sample: 49,17,56,85,12,97,33,71,19,62,38,84,51,29,77,65,44,99,4,47,67,41,23,88,73,8,100,25,91,58,59,22,15,35,95,60,20,7,50,10
****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATA_NUM 40

void bubble_sort(int value[], int size)
{
    int temp = 0;

    for (int i = 0; i < (size - 1); ++i) {
        for (int j = (size - 1); j > i; --j) {
            if (value[j-1] > value[j]) {
                temp = value[j-1];
                value[j-1] = value[j];
                value[j] = temp;
            }
        }
    }
}

void swap(int *p_from, int *p_to)
{
    int tmp;
    tmp = *p_from;
    *p_from = *p_to;
    *p_to = tmp;
}

void insertion_sort(int value[], int size)
{
    int j;

    for (int i=1; i < size; ++i) {
        j = i;
        while ((j > 0) && (value[j-1] > value[j])) {
            swap(&value[j-1], &value[j]);
            j--;
        }
    }
}

void shell_sort(int value[], int size)
{
    int j;
    int temp;
    int increment = 4;

    while (increment > 0)
    {
        for (int i=0; i < size; ++i)
        {
            j = i;
            temp = value[i];
            while ((j >= increment) && (value[j-increment] > temp))
            {
                value[j] = value[j - increment];
                j = j - increment;
            }
            value[j] = temp;
        }
        if (increment/2 != 0)
            increment = increment/2;
        else if (increment == 1)
            increment = 0;
        else
            increment = 1;
    }
}

void selection_sort(int value[], int size)
{
    int min;
    int temp;

    for (int i = 0; i < size-1; ++i) {
        min = i;
        for (int j = i+1; j < size; ++j) {
            if (value[j] < value[min]) {
                min = j;
            }
        }
        temp = value[i];
        value[i] = value[min];
        value[min] = temp;
    }
}

void q_move(int value[], int left, int right)
{
    int pivot, l_hold, r_hold;

    l_hold = left;
    r_hold = right;
    pivot = value[left];
    while (left < right)
    {
        while ((value[right] >= pivot) && (left < right))
            right--;
        if (left != right)
        {
            value[left] = value[right];
            left++;
        }
        while ((value[left] <= pivot) && (left < right))
            left++;
        if (left != right)
        {
            value[right] = value[left];
            right--;
        }
    }
    value[left] = pivot;
    pivot = left;
    left = l_hold;
    right = r_hold;
    if (left < pivot)
        q_move(value, left, pivot-1);
    if (right > pivot)
        q_move(value, pivot+1, right);
}

void quick_sort(int value[], int size)
{
    q_move(value, 0, size-1);
}

int main(){
    FILE *lf;
    char bff[DATA_NUM*4];
    char *value_a;
    int value[DATA_NUM];
    int value_sorted[DATA_NUM];
    int value_index;

    /* file open */
    if(!(lf=fopen("input.csv","r"))){
        printf("File open error.\n");
        return -1;
    }

    /* read data */
    fgets(bff, DATA_NUM*4, lf);
    value_index = 0;
    for(value_a=strtok(bff, ","); value_a!=NULL; value_a=strtok(NULL, ",")) {
        value[value_index] = atoi(value_a);
        value_index += 1;
    }

    /* initial data */
    printf("Initial data.\n");
    for (int i = 0; i < DATA_NUM; ++i) printf("%d, ", value[i]);
    printf("\n\n");

    /* bubble sort */
    for (int i = 0; i < DATA_NUM; ++i) value_sorted[i] = value[i];
    bubble_sort(value_sorted, DATA_NUM);
    printf("Bubble sorted.\n");
    for (int i = 0; i < DATA_NUM; ++i) printf("%d, ", value_sorted[i]);
    printf("\n\n");

    /* insertion sort */
    for (int i = 0; i < DATA_NUM; ++i) value_sorted[i] = value[i];
    insertion_sort(value_sorted, DATA_NUM);
    printf("Insertion sorted.\n");
    for (int i = 0; i < DATA_NUM; ++i) printf("%d, ", value_sorted[i]);
    printf("\n\n");

    /* shell sort */
    for (int i = 0; i < DATA_NUM; ++i) value_sorted[i] = value[i];
    shell_sort(value_sorted, DATA_NUM);
    printf("Shell sorted.\n");
    for (int i = 0; i < DATA_NUM; ++i) printf("%d, ", value_sorted[i]);
    printf("\n\n");

    /* selection sort */
    for (int i = 0; i < DATA_NUM; ++i) value_sorted[i] = value[i];
    selection_sort(value_sorted, DATA_NUM);
    printf("Selection sorted.\n");
    for (int i = 0; i < DATA_NUM; ++i) printf("%d, ", value_sorted[i]);
    printf("\n\n");

    /* quick sort */
    for (int i = 0; i < DATA_NUM; ++i) value_sorted[i] = value[i];
    quick_sort(value_sorted, DATA_NUM);
    printf("Quick sorted.\n");
    for (int i = 0; i < DATA_NUM; ++i) printf("%d, ", value_sorted[i]);
    printf("\n\n");

    /* file close */
    fclose(lf);

    return 0;
}