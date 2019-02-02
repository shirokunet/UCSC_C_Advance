/****************************************************
Prologue
University of California Extension, Santa Cruz
Advanced C Programming
Instructor: Rajainder A. Yeldandi
Author: Reyes
Assignment Number: 4
Topic: File operation.
file name: assignment.c
Date: Feb 1, 2019
Objective: Practice.
Comments: None.
Input sample: 
91, 92, 85, 58, 87, 75, 89, 97, 79, 65, 
88, 72, 81, 94, 90, 61, 72, 75, 68, 77, 
75, 49, 87, 79, 65, 64, 62, 51, 44, 70, 
81, 72, 85, 78, 77, 75, 79, 87, 69, 55,
88, 62, 71, 74, 80, 71, 62, 85, 68, 87, 
75, 89, 97, 79, 65, 48, 72, 61, 64, 90
****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STUDENT_SUM 6
#define EXAM_SUM 10

typedef struct
{
    int num;
    int min;
    int max;
    int tot;
    int avg;
    char grade[100];
} result;

result calc_min_max_avg(int data[EXAM_SUM]){
    static int num = 0;

    result exam_result;
    test.num = num;
    test.min = 0;
    test.max = 0;
    test.tot = 0;
    test.avg = 0;

    for (int i = 0; i < EXAM_SUM; ++i)
    {
        if (test.min == 0 || test.min > data[i])
            test.min = data[i];
        if (test.max == 0 || test.max < data[i])
            test.max = data[i];
        if (test.avg == 0)
            test.avg = data[i];
        test.tot += data[i];

        test.grade = 
    }

    test.avg = test.tot / EXAM_SUM;

    printf("Num: %d\n", test.num);
    printf("Min: %d\n", test.min);
    printf("Max: %d\n", test.max);
    printf("Avg: %d\n", test.avg);

    num += 1;

    return exam_result;
}

int main(){
    FILE *lf,*sf;

    /* file open */
    if(!(lf=fopen("input.csv","r")) || (!(sf=fopen("output.csv","w")))){
        printf("File open error.\n");
        return -1;
    }

    char bff[100];
    char *value_a;
    int value[STUDENT_SUM][EXAM_SUM];
    int value_num;
    result exam;

    for(int i = 0 ; i < STUDENT_SUM ; i++){

        /* read data */
        fgets(bff, 100, lf);
        value_num = 0;
        for(value_a=strtok(bff, ","); value_a!=NULL; value_a=strtok(NULL, ",")) {
            value[i][value_num] = atoi(value_a);
            printf("%d,", value[i][value_num]);
            value_num += 1;
        }
        printf("\n");

        /* calc data */
        exam = calc_min_max_avg(value[i]);
        printf("\n");

        /* write data */
        for(int i = 0 ; i < STUDENT_SUM ; i++){
            fprintf(sf, "Student ID: %d¥n", exam.num);
            fprintf(sf, "Minimum: %d, Maximum: %d, Average: %d\n", exam.min, exam.max, exam.avg);
        }
    }

    /* file close */
    fclose(sf);
    fclose(lf);

    return 0;
}