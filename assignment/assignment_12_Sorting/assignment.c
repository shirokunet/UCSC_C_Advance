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

#define DATA_NUM 50

void bubble_sort(int value[], int size)
{
    int temp = 0;

    for (int i = 0; i < (size - 1); ++i)
    {
        for (int j = (size - 1); j > i; --j)
        {
            if (value[j-1] > value[j])
            {
                temp = value[j-1];
                value[j-1] = value[j];
                value[j] = temp;
            }
        }
    }
}

void swap(int *p_from, int *p_to)
{
    int tmp = *p_from;
    *p_from = *p_to;
    *p_to = tmp;
}

void insertion_sort(int value[], int size)
{
    int j;

    for (int i=1; i < size; ++i)
    {
        j = i;
        while ((j > 0) && (value[j-1] > value[j]))
        {
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

    for (int i = 0; i < size-1; ++i)
    {
        min = i;
        for (int j = i+1; j < size; ++j)
        {
            if (value[j] < value[min])
                min = j;
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
        q_move(value, left, pivot - 1);
    if (right > pivot)
        q_move(value, pivot + 1, right);
}

void quick_sort(int value[], int size)
{
    q_move(value, 0, size - 1);
}

void h_down (int value[], int first, int last)
{
    int parent = first;
    int child = 2 * parent + 1;

    while (child <= last)
    {
        if ((child < last) && (value[child] < value[child + 1]))
            child++;
        if (value[child] <= value[parent])
            break;
        swap(&value[child], &value[parent]);
        parent = child;
        child = 2 * parent + 1;
    }
}

void heap_sort (int value[], int size)
{
    size = size - 1;

    for (int i = size / 2; i >= 0; --i)
        h_down(value, i, size);

    for (int i = size; i >= 1; --i)
    {
        swap(&value[0], &value[i]);
        h_down(value, 0, i - 1);
    }
}

// void h_sort (int value[], int size, int root)
// {
//     int max;

//     while(1)
//     {
//         max = root * 2 + 1;
//         if (root * 2 + 2 <= size)
//         {
//             if(value[root * 2 + 1] < value[root * 2 + 2])
//                 max = root * 2 + 2;
//         }
//         else if (!(root * 2 + 1 <= size))
//             break;

//         if (value[root] < value[max])
//         {
//             swap(&value[root], &value[max]);
//             root = max;
//         }
//         else
//             break;
//     }
//     return;
// }

// void heap_sort (int value[], int size)
// {
//     for (int i = size/2; i >= 0; --i)
//         h_sort(value,size,i);

//     while(1)
//     {
//         swap(&value[0], &value[size--]);
//         if (!size)
//             break;
//         h_sort(value, size,0);
//     }
//     return;
// }

void m_sort (int value[], int left, int right)
{
    int i, j, mid;
    int work[DATA_NUM];

    if (left < right)
    {
        mid = (left + right) / 2;
        m_sort(value, left, mid);
        m_sort(value, mid+1, right);

        for (i = mid; i >= left; --i)
            work[i] = value[i];
        for (j = mid+1; j <= right; ++j)
            work[right-(j-(mid+1))] = value[j];

        i = left;
        j = right;

        for (int k = left; k <= right; ++k)
        {
          if (work[i] < work[j])
            value[k] = work[i++];
          else
            value[k] = work[j--];
        }
    }
}

void merge_sort(int value[], int size)
{
    m_sort(value, 0, size - 1);
}

void read_csvfile(int value[DATA_NUM], int *value_index)
{
    FILE *lf;
    char bff[DATA_NUM * 4];
    char *value_a;
    // int value_index;

    /* file open */
    if(!(lf=fopen("input.csv","r"))){
        printf("File open error.\n");
        return;
    }

    /* read data */
    fgets(bff, DATA_NUM*4, lf);
    // value_index = 0;
    for (value_a=strtok(bff, ","); value_a!=NULL; value_a=strtok(NULL, ","))
    {
        value[*value_index] = atoi(value_a);
        *value_index += 1;
    }

    /* file close */
    fclose(lf);
}

int main()
{
    int value_size;
    int value[DATA_NUM];
    int value_sorted[DATA_NUM];
    char str[2];

    read_csvfile(value, &value_size);
    printf("%d\n", value_size);

    printf("|o: Original data from  csv.  |\n");
    printf("|b: Bubble sort.              |\n");
    printf("|i: Insertion sort.           |\n");
    printf("|s: Shell sort.               |\n");
    printf("|n: Selection sorted.         |\n");
    printf("|q: Quick sort.               |\n");
    printf("|h: Heap sort.                |\n");
    printf("|m: Merge sort.               |\n");
    printf("|e: End this program.         |\n\n");


    while(1)
    {
        printf("Enter a above command: ");
        scanf("%s", str);

        for (int i = 0; i < value_size; ++i)
            value_sorted[i] = value[i];

        switch (*str)
        {
            case 'o':
                break;
            case 'b':
                bubble_sort(value_sorted, value_size);
                break;
            case 'i':
                insertion_sort(value_sorted, value_size);
                break;
            case 's':
                shell_sort(value_sorted, value_size);
                break;
            case 'n':
                selection_sort(value_sorted, value_size);
                break;
            case 'q':
                quick_sort(value_sorted, value_size);
                break;
            case 'h':
                heap_sort(value_sorted, value_size);
                break;
            case 'm':
                merge_sort(value_sorted, value_size);
                break;
            case 'e':
                return 0;
            default :
                printf("Could not find your command.\n\n");
                return 0;
        }

        for (int i = 0; i < value_size; ++i)
        {
            printf("%d,", value_sorted[i]);
            value_sorted[i] = 0;
        }

        printf("\n\n");
    }

    return 0;
}