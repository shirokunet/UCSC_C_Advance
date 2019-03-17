/****************************************************
Prologue
University of California Extension, Santa Cruz
Advanced C Programming
Instructor: Rajainder A. Yeldandi
Author: Reyes
Assignment Number: 14
Topic: BTrees.
file name: assignment.c
Date: Mar 16, 2019
Objective: Practice.
Comments: None.
Input csv sample:
572, 430, 315, 363, 320, 545, 451, 437, 476, 472, 493, 395, 462, 521, 406,
412, 510, 560, 425, 595, 580, 583, 531, 511, 459, 518, 356, 379, 488, 532
****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define NUM 4    // Half of data size

struct btreenode {
    int numtrees;
    int key[2 * NUM];
    struct btreenode *branch[2 * NUM + 1];
};
typedef struct btreenode* BTREEP;

BTREEP make_btreenode(void)
{
    BTREEP p;
    if ((p = malloc(sizeof *p)) == NULL)
    {
        printf("It doesn't have enough memory size.\n");
        exit(EXIT_FAILURE);
    }
    return p;
}

void search_userinput(BTREEP root, int key)
{
    BTREEP p = root;
    int k;

    while (p != NULL)
    {
        k = 0;
        while (k < p->numtrees && p->key[k] < key)
            k++;
        if (k < p->numtrees && p->key[k] == key)
        {
            printf(" %d\tFound!\n", key);
            return;
        }
        p = p->branch[k];
    }
    printf(" %d\tCould not find...\n", key);
}

void insert_node(BTREEP p, int k, int key, BTREEP newp)
{
    for (int i = p->numtrees; i > k; i--)
    {
        p->key[i] = p->key[i - 1];
        p->branch[i + 1] = p->branch[i];
    }
    p->key[k] = key;
    p->branch[k + 1] = newp;
    p->numtrees++;
}

void split_node(BTREEP p, int k, int *key, BTREEP *newp)
{
    int m = 0;
    BTREEP q = make_btreenode();

    if (k <= NUM)
        m = NUM;
    else
        m = NUM + 1;

    for (int j = m + 1; j <= 2 * NUM; j++)
    {
        q->key[j - m - 1] = p->key[j - 1];
        q->branch[j - m] = p->branch[j];
    }
    q->numtrees = 2 * NUM - m;  p->numtrees = m;

    if (k <= NUM)
        insert_node(p, k, *key, *newp);
    else
        insert_node(q, k - m, *key, *newp);

    q->branch[0] = p->branch[p->numtrees];
    p->numtrees--;

    *key = p->key[p->numtrees - 1];
    *newp = q;
}

void insert_node_rec(BTREEP p, int *key, bool *done, BTREEP *newp)
{
    int k = 0;

    if (p == NULL) {
        *done = false;
        *newp = NULL;
        return;
    }

    while (k < p->numtrees && p->key[k] < *key)
        k++;

    if (k < p->numtrees && p->key[k] == *key)
    {
        printf("The tree already has the value.\n");
        *done = true;
        return;
    }

    insert_node_rec(p->branch[k], key, done, newp);
    if (*done)
        return;

    if (p->numtrees < 2 * NUM)  // Can not split_node tree.
    {   
        insert_node(p, k, *key, *newp);
        *done = true;
    }
    else    // Can split_node tree.
    {
        split_node(p, k, key, newp);
        *done = false;
    }
}

void insert_userinput(BTREEP *root, int key)
{
    BTREEP p;
    bool done;
    BTREEP newp;

    // printf("Subscriped the value.\n");

    insert_node_rec(*root, &key, &done, &newp);
    if (done)
        return;

    p = make_btreenode();
    p->numtrees = 1;
    p->key[0] = key;
    p->branch[0] = *root;
    p->branch[1] = newp;

    *root = p;
}

void remove_node(BTREEP p, int k, bool *undersize)
{
    while (++k < p->numtrees)
    {
        p->key[k - 1] = p->key[k];
        p->branch[k] = p->branch[k + 1];
    }
    *undersize = --(p->numtrees) < NUM;
}

void move_rightnode(BTREEP p, int k)
{
    BTREEP left  = p->branch[k - 1];
    BTREEP right = p->branch[k];

    for (int j = right->numtrees; j > 0; j--)
    {
        right->key[j] = right->key[j - 1];
        right->branch[j + 1] = right->branch[j];
    }

    right->branch[1] = right->branch[0];
    right->numtrees++;
    right->key[0] = p->key[k - 1];
    p->key[k - 1] = left->key[left->numtrees - 1];
    right->branch[0] = left->branch[left->numtrees];
    left->numtrees--;
}

void move_leftnode(BTREEP p, int k)
{
    BTREEP left  = p->branch[k - 1];
    BTREEP right = p->branch[k];

    left->numtrees++;
    left->key[left->numtrees - 1] = p->key[k - 1];
    left->branch[left->numtrees] = right->branch[0];
    p->key[k - 1] = right->key[0];
    right->branch[0] = right->branch[1];
    right->numtrees--;

    for (int j = 1; j <= right->numtrees; j++)
    {
        right->key[j - 1] = right->key[j];
        right->branch[j] = right->branch[j + 1];
    }
}

void combilne_node(BTREEP p, int k, bool *undersize)
{
    BTREEP left  = p->branch[k - 1];
    BTREEP right = p->branch[k];

    left->numtrees++;
    left->key[left->numtrees - 1] = p->key[k - 1];
    left->branch[left->numtrees] = right->branch[0];

    for (int j = 1; j <= right->numtrees; j++)
    {
        left->numtrees++;
        left->key[left->numtrees - 1] = right->key[j - 1];
        left->branch[left->numtrees] = right->branch[j];
    }

    remove_node(p, k - 1, undersize);
    free(right);
}

void restore_node(BTREEP p, int k, bool *undersize)
{
    *undersize = false;

    if (k > 0)
    {
        if (p->branch[k - 1]->numtrees > NUM)
            move_rightnode(p, k);
        else
            combilne_node(p, k, undersize);
    }
    else
    {
        if (p->branch[1]->numtrees > NUM)
            move_leftnode(p, 1);
        else
            combilne_node(p, 1, undersize);
    }
}

void delete_node(BTREEP p, int *key, bool *deleted)
{
    int k = 0;
    BTREEP q;
    bool undersize = false;

    if (p == NULL)  // Could not find.
        return;

    while (k < p->numtrees && p->key[k] < *key)
        k++;

    if (k < p->numtrees && p->key[k] == *key)   // Found.
    {
        *deleted = true;
        if ((q = p->branch[k + 1]) != NULL)
        {
            while (q->branch[0] != NULL)
                q = q->branch[0];
            p->key[k] = *key = q->key[0];
            delete_node(p->branch[k + 1], key, deleted);
            if (undersize)
                restore_node(p, k + 1, &undersize);
        }
        else
            remove_node(p, k, &undersize);
    }
    else
    {
        delete_node(p->branch[k], key, deleted);
        if (undersize)
            restore_node(p, k, &undersize);
    }
}

void delete_userinput(BTREEP *root, int key)
{
    BTREEP p;
    bool deleted = false;
    delete_node(*root, &key, &deleted);

    if (deleted)
    {
        if ((*root)->numtrees == 0)
        {
            p = *root;  *root = (*root)->branch[0];
            free(p);
        }
        // printf(" %d\tDeleted!\n", key);
    }
    // else
    //     printf(" %d\tCould not find...\n", key);
}

void traverse(BTREEP p)
{
    static int depth = 0;

    if (p == NULL)
        return;

    printf("[");
    depth++;
    for (int k = 0; k < p->numtrees; k++)
    {
        traverse(p->branch[k]);
        printf(" %d ", p->key[k]);
    }
    traverse(p->branch[p->numtrees]);
    printf("]");
    depth--;
}

void read_csvfile(BTREEP *root)
{
    FILE *lf;
    char bff[1000];
    char *value_a;

    if (!(lf=fopen("input.csv","r")))
        printf("File open error.\n");

    fgets(bff, 1000, lf);
    for (value_a=strtok(bff, ","); value_a!=NULL; value_a=strtok(NULL, ","))
        insert_userinput(&(*root), atoi(value_a));

    fclose(lf);
}

int main()
{
    char str[2];
    BTREEP root = NULL;
    int key = 0;

    while(1)
    {
        printf("|r: Read csv data into the tree.         |\n");
        printf("|t: Traverse nodes in the tree.          |\n");
        printf("|p: Put a node in the tree.              |\n");
        printf("|d: Delete a node in the tree.           |\n");
        printf("|s: Serch an array of value in the tree. |\n");
        printf("|e: End this program.                    |\n\n");

        printf("Enter a above command: ");
        scanf("%s", str);

        switch (*str)
        {
            case 'r':
                read_csvfile(&root);
                break;
            case 't':
                traverse(root);
                printf("\n");
                break;
            case 'p':
                printf ("Enter a value you want to put: ");
                scanf("%d", &key);
                insert_userinput(&root, key);
                break;
            case 'd':
                printf ("Enter a value you want to delete: ");
                scanf("%d", &key);
                delete_userinput(&root, key);
                break;
            case 's':
                printf ("Enter a array of value you want to serch: ");
                scanf("%d", &key);
                search_userinput(root, key);
                break;
            case 'e':
                return 0;
            default :
                printf("Could not find your command.\n\n");
                break;
        }

        printf("\n");
    }

    return 0;
}