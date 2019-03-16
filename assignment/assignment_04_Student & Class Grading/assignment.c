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
91,92,85,58,87,75,89,97,79,65
88,72,81,94,90,61,72,75,68,77
75,49,87,79,65,64,62,51,44,70
81,72,85,78,77,75,79,87,69,55
88,62,71,74,80,71,62,85,68,87
75,89,97,79,65,48,72,61,64,90
****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STUDENT_SUM 6
#define EXAM_SUM 10

typedef struct
{
    int num;
    int scr[EXAM_SUM];
    int min;
    int max;
    int tot;
    int avg;
    char grd[EXAM_SUM][5];
} result;

result grading(int data[EXAM_SUM]){
    static int num = 1000;

    result exam;
    exam.num = num;
    exam.min = 0;
    exam.max = 0;
    exam.tot = 0;
    exam.avg = 0;

    for (int i = 0; i < EXAM_SUM; ++i)
    {
        exam.scr[i] = data[i];
        if (exam.min == 0 || exam.min > data[i])
            exam.min = data[i];
        if (exam.max == 0 || exam.max < data[i])
            exam.max = data[i];
        if (exam.avg == 0)
            exam.avg = data[i];
        exam.tot += data[i];

        if (data[i] > 95)
            strcpy(exam.grd[i], "A+");
        else if (data[i] == 95)
            strcpy(exam.grd[i], "A");
        else if (data[i] >= 90)
            strcpy(exam.grd[i], "A-");
        else if (data[i] > 85)
            strcpy(exam.grd[i], "B+");
        else if (data[i] == 85)
            strcpy(exam.grd[i], "B");
        else if (data[i] >= 80)
            strcpy(exam.grd[i], "B-");
        else if (data[i] > 75)
            strcpy(exam.grd[i], "C+");
        else if (data[i] == 75)
            strcpy(exam.grd[i], "C");
        else if (data[i] >= 70)
            strcpy(exam.grd[i], "C-");
        else if (data[i] >= 60)
            strcpy(exam.grd[i], "D");
        else if (data[i] < 60)
            strcpy(exam.grd[i], "F");
    }

    exam.avg = exam.tot / EXAM_SUM;
    num += 1;

    return exam;
}

int main(){
    FILE *lf,*sf;
    char bff[100];
    char *value_a;
    int value[STUDENT_SUM][EXAM_SUM];
    int value_num;
    result exam;

    /* file open */
    if(!(lf=fopen("input.csv","r")) || (!(sf=fopen("output.csv","w")))){
        printf("File open error.\n");
        return -1;
    }

    for(int i = 0 ; i < STUDENT_SUM ; i++){
        /* read data */
        fgets(bff, 100, lf);
        value_num = 0;
        for(value_a=strtok(bff, ","); value_a!=NULL; value_a=strtok(NULL, ",")) {
            value[i][value_num] = atoi(value_a);
            value_num += 1;
        }

        /* calc data */
        exam = grading(value[i]);

        /* check data */
        printf("Student ID: %d\n", exam.num);
        printf("Minimum: %d, Maximum: %d, Average: %d\n", exam.min, exam.max, exam.avg);
        for (int j = 0; j < EXAM_SUM; ++j)
        {
            printf("Score: %d, Grade: %s\n", exam.scr[j], exam.grd[j]);
        }
        printf("\n");

        /* write data */
        fprintf(sf, "Student ID: %d\n", exam.num);
        fprintf(sf, "Minimum: %d, Maximum: %d, Average: %d\n", exam.min, exam.max, exam.avg);
        for (int j = 0; j < EXAM_SUM; ++j)
        {
            fprintf(sf, "Score: %d, Grade: %s\n", exam.scr[j], exam.grd[j]);
        }
        fprintf(sf, "\n");
    }

    /* file close */
    fclose(sf);
    fclose(lf);

    return 0;
}