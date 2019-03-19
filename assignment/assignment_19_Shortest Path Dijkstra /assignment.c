/****************************************************
Prologue
University of California Extension, Santa Cruz
Advanced C Programming
Instructor: Rajainder A. Yeldandi
Author: Reyes
Assignment Number: 19
Topic: Shortest Path (Dijkstra).
file name: assignment.c
Date: Mar 19, 2019
Objective: Practice.
Comments: None.
Input csv sample:
s,0
d,7
0,1,25
1,2,65
1,3,35
1,4,85
2,5,50
3,2,60
3,4,40
4,5,120
5,7,25
6,5,55
6,7,95
****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define INF 10000
#define SIZE 100

void init(int DIST[SIZE][SIZE], int VIA[SIZE])
{
    /* init VIA and DIST */
    for (int i = 0; i < SIZE; ++i)
    {
        VIA[i] = -1;
        for (int j = 0; j < SIZE; ++j)
            DIST[i][j] = INF;
    }
}

void read_csvfile(int path[SIZE][SIZE], int *start, int *destination)
{
    FILE *lf;
    char bff[100];
    int a = 0;
    int b = 0;
    int l = 0;

    if (!(lf=fopen("input.csv","r")))
        printf("File open error.\n");

    /* get start point*/
    fgets(bff, 100, lf);
    strtok(bff, ",");
    *start = atoi(strtok(NULL, ","));

    /* get destination point*/
    fgets(bff, 100, lf);
    strtok(bff, ",");
    *destination = atoi(strtok(NULL, ","));

    /* get nodes */
    while (fgets(bff, 100, lf) != NULL)
    {
        a = atoi(strtok(bff, ","));
        b = atoi(strtok(NULL, ","));
        l = atoi(strtok(NULL, ","));
        path[a][b] = l;
    }

    fclose(lf);
}

void show_nodes(int DIST[SIZE][SIZE], int s, int d)
{
    printf("Start:       %d\n", s);
    printf("Destination: %d\n\n", d);

    printf("Nodes:\n");
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            if (DIST[i][j] < INF)
                printf("%d->%d: %d\n", i, j, DIST[i][j]);
    printf("\n");
}

void show_path(int VIA[SIZE], int s, int d)
{
    printf("Shortest path:\n");
    printf("%d", d);
    while(1)
    {
        d = VIA[d];
        printf("->%d", d);
        if (d == s) break;
    }
    printf("\n\n");
}

int dijkstra(int DIST[SIZE][SIZE], int VIA[SIZE], int start, int goal)
{
    int min = 0;
    int target = 0;
    int N = 0;

    int COST[SIZE];
    char USED[SIZE];

    /* init COST and USED */
    for (int i = 0; i < SIZE; ++i)
    {
        COST[i] = INF;
        USED[i] = false;
    }
    COST[start] = 0;

    /* define N */
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            if (DIST[i][j] < INF && N < j)
                N = j;
    N += 1;

    /* dijkstra */
    while (1)
    {
        min = INF;
        for (int i = 0; i < N; ++i)
        {
            if (!USED[i] && min > COST[i])
            {
                min = COST[i];
                target = i;
            }
        }

        if(target == goal)
            return COST[goal];

        for (int neighbor = 0; neighbor < N; ++neighbor)
        {
            if (COST[neighbor] > DIST[target][neighbor] + COST[target])
            {
                COST[neighbor] = DIST[target][neighbor] + COST[target];
                VIA[neighbor] = target;
            }
        }
        USED[target] = true;
    }
}

int main(void){
    int DIST[SIZE][SIZE];
    int VIA[SIZE];
    int s = 0;  // start
    int d = 0;  // destination
    int c = 0;  // total cost

    init(DIST, VIA);

    read_csvfile(DIST, &s, &d);

    show_nodes(DIST, s, d);

    c = dijkstra(DIST, VIA, s, d);

    show_path(VIA, s, d);

    printf("Total cost: %d\n\n", c);

    return 0;
}