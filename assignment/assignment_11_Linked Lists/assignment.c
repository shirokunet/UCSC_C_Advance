/****************************************************
Prologue
University of California Extension, Santa Cruz
Advanced C Programming
Instructor: Rajainder A. Yeldandi
Author: Reyes
Assignment Number: 11
Topic: Linked Lists
file name: assignment.c
Date: Mar 3, 2019
Objective: Practice.
Comments: None.
Input csv sample:
49, 17, 56, 85, 12, 97, 33, 71, 19, 62, 38, 84, 51,
29, 77, 65, 44, 99, 4, 47, 67, 41, 23, 88, 73, 8, 10,
100, 25, 91, 58, 45, 22, 15, 35, 95, 60, 20, 7, 50
****************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct listnode {
    int data;
    struct listnode*  nextptr;
};

typedef struct listnode LISTNODE;

void init_head(LISTNODE *sptr)
{
    sptr->data = 0;
    sptr->nextptr = NULL;
}

LISTNODE* search_end_node(LISTNODE *sptr)
{
    LISTNODE* p = sptr;

    while (p->nextptr != NULL)
        p = p->nextptr;

    return p;
}

void add_node(LISTNODE *sptr, int data)
{
    LISTNODE* elem;
    LISTNODE* tail;

    tail = search_end_node(sptr);

    elem = malloc(sizeof(LISTNODE));
    if (elem == NULL)
    {
        fputs("Could not allocate memory.", stderr);
        exit(1);
    }
    elem->data = data;
    elem->nextptr = NULL;

    tail->nextptr = elem;
}

int delete_node(LISTNODE *sptr, int data)
{
    LISTNODE* p = sptr->nextptr;
    LISTNODE* prev = sptr;
    int count = 0;

    while (p != NULL)
    {
        if (p->data == data)
        {
            prev->nextptr = p->nextptr;
            free(p);
            p = prev->nextptr;
            ++count;
        }
        else
        {
            prev = p;
            p = p->nextptr;
        }
    }

    return count;
}

void clear_list(LISTNODE *sptr)
{
    LISTNODE* p = sptr->nextptr;
    LISTNODE* prev = sptr;

    while (p != NULL)
    {
        prev->nextptr = p->nextptr;
        free( p );
        p = prev->nextptr;
    }
}

LISTNODE* search_node(LISTNODE *sptr, int data)
{
    LISTNODE* p = sptr->nextptr;

    while (p != NULL)
    {
        if (p->data == data)
        {
            printf(" %d\tFound!\n", data);
            return p;
        }
        p = p->nextptr;
    }

    printf(" %d\tCould not find...\n", data);
    return NULL;
}

void print_list(LISTNODE *sptr)
{
    LISTNODE* p = sptr->nextptr;

    if (p == NULL)
    {
        puts("The list is empty.");
        return;
    }

    while (p != NULL)
    {
        printf( "%d,", p->data );
        p = p->nextptr;
    }
    printf("\n");
}

void reverse_list(LISTNODE *sptr)
{
    LISTNODE* p = sptr->nextptr;
    LISTNODE* work = NULL;
    LISTNODE* tmp;

    while (p != NULL)
    {
        tmp = p->nextptr;
        p->nextptr = work;
        work = p;
        p = tmp;
    }

    sptr->nextptr = work;
}

void read_csvfile(LISTNODE *sptr)
{
    FILE *lf;
    char bff[1000];
    char *data_a;

    if (!(lf=fopen("input.csv","r")))
        printf("File open error.\n");

    fgets(bff, 1000, lf);
    for (data_a=strtok(bff, ","); data_a!=NULL; data_a=strtok(NULL, ","))
        add_node(sptr, atoi(data_a));

    fclose(lf);
}


int main(void)
{
    LISTNODE sptr;
    char str[2];
    int data;

    init_head(&sptr);

    printf("|c: Read csv data into the linked list.    |\n");
    printf("|p: Print data in the linked list.         |\n");
    printf("|a: Add a data into the linked list.       |\n");
    printf("|d: Delete a data in the linked list.      |\n");
    printf("|s: Search a data in the linked list.      |\n");
    printf("|r: Reverse the other of the linked list.  |\n");
    printf("|i: Init the linked list.                  |\n");
    printf("|e: End this program.                      |\n\n");

    while(1)
    {
        printf("Enter a above command: ");
        scanf("%s", str);

        switch (*str)
        {
            case 'c':
                read_csvfile(&sptr);
                break;
            case 'p':
                print_list(&sptr);
                break;
            case 'a':
                printf ("Enter a data you want to put: ");
                scanf("%d", &data);
                add_node(&sptr, data);
                break;
            case 'd':
                printf ("Enter a data you want to delete: ");
                scanf("%d", &data);
                delete_node(&sptr, data);
                break;
            case 's':
                printf ("Enter a data you want to search: ");
                scanf("%d", &data);
                search_node(&sptr, data);
                break;
            case 'r':
                reverse_list(&sptr);
                break;
            case 'i':
                init_head(&sptr);
                break;
            case 'e':
                return 0;
            default :
                printf("Could not find your command.\n");
                break;
        }

        printf("\n");
    }

    return 0;
}
