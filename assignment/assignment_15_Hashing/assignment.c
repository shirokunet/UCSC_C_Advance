/****************************************************
Prologue
University of California Extension, Santa Cruz
Advanced C Programming
Instructor: Rajainder A. Yeldandi
Author: Reyes
Assignment Number: 15
Topic: Hash Table.
file name: assignment.c
Date: Mar 17, 2019
Objective: Practice.
Comments: None.
Input csv sample:
UCSC-1000,0
UCSC-1001,1
UCSC-1002,2
UCSC-1003,3
UCSC-1004,4
...
UCSC-1095,95
UCSC-1096,96
UCSC-1097,97
UCSC-1098,98
UCSC-1099,99
****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define TABLESIZE 15

typedef char* KEYTYPE;
typedef int RECTYPE;

typedef struct node {
    KEYTYPE key;
    RECTYPE record;
    struct node *next;
} table;

typedef struct {
    int size;
    int count;
    table **table;
} htable;

htable *make_hash_table(int size)
{
    htable *ht = malloc(sizeof(htable));
    if (ht != NULL)
    {
        ht->size = size;
        ht->count = 0;
        ht->table = malloc(sizeof(table *) * size);
        if (ht->table == NULL)
        {
            free(ht);
            return NULL;
        }
        for (int i = 0; i < size; ++i)
            ht->table[i] = NULL;
    }
    return ht;
}

table *make_table(KEYTYPE key, RECTYPE rec, table *next)
{
    table *cp = malloc(sizeof(table));
    if (cp != NULL)
    {
        cp->key = malloc(strlen(key) + 1);
        if (cp->key == NULL)
        {
            free(cp);
            return NULL;
        }
        strcpy(cp->key, key);
        cp->record = rec;
        cp->next = next;
    }
    return cp;
}

int hash_func(htable *ht, KEYTYPE key)
{
    unsigned h = 0;
    while(*key)
        h += *key++;
    return(h % ht->size);
}

table *search_table(htable *ht, KEYTYPE key, int hval)
{
    table *cp = ht->table[hval];
    for (; cp != NULL; cp = cp->next)
    {
        if (strcmp(cp->key, key) == 0)
            return cp;
    }
    return NULL;
}

int search_hash(htable *ht, KEYTYPE key, bool *err)
{
    table *cp = search_table(ht, key, hash_func(ht, key));
    if (cp != NULL)
    {
        *err = true;
        return cp->record;
    }
    *err = false;
    return -1;
}

bool insert_hash(htable *ht, KEYTYPE key, RECTYPE rec)
{
    int hval = hash_func(ht, key);
    table *cp = search_table(ht, key, hval);
    if (cp == NULL)
    {
        ht->table[hval] = make_table(key, rec, ht->table[hval]);
        ht->count++;
        return true;
    }
    else
    {
        cp->record = rec;
        return false;
    }
}

void delete_table(table *cp)
{
    while (cp != NULL)
    {
        table *xs = cp->next;
        free(cp->key);
        free(cp);
        cp = xs;
    }
}

void delete_hash_table(htable *ht)
{
    for (int i = 0; i < ht->size; ++i)
        delete_table(ht->table[i]);
    free(ht);
}

bool delete_hash(htable *ht, KEYTYPE key)
{
    int hval = hash_func(ht, key);
    table *cp = ht->table[hval];
    if (cp != NULL)
    {
        if (strcmp(cp->key, key) == 0)
        {
            ht->table[hval] = cp->next;
            ht->count--;
            free(cp->key);
            free(cp);
            return true;
        }
        else
        {
            for (; cp->next != NULL; cp = cp->next)
            {
                if (strcmp(cp->next->key, key) == 0)
                {
                    table *del = cp->next;
                    cp->next = cp->next->next;
                    ht->count--;
                    free(del->key);
                    free(del);
                    return true;
                }
            }
        }
    }
    return false;
}

void traverse_table(htable *ht)
{
    for (int i = 0; i < ht->size; ++i)
    {
        table *cp = ht->table[i];
        printf("[Tabel %d]\n", i);
        for (; cp != NULL; cp = cp->next)
        {
            printf("%s,%d\n", cp->key, cp->record);
        }
        printf("\n");
    }
    printf("size: %d\n", ht->count);
}

int read_csvfile(htable *ht)
{
    FILE *lf;
    char bff[100];
    KEYTYPE key;
    RECTYPE rec;

    if (!(lf=fopen("input.csv","r")))
    {
        printf("File open error.\n");
        return 0;
    }

    while (fgets(bff, 100, lf) != NULL)
    {
        key = strtok(bff, ",");
        rec = atoi(strtok(NULL, ","));
        insert_hash(&(*ht), key, rec);
    }

    fclose(lf);

    return 1;
}

int main(void)
{
    htable *ht = make_hash_table(TABLESIZE);
    bool err = false;
    char str[2];
    char key[10];
    int rec;

    printf("|r: Read csv data into the hash table.  |\n");
    printf("|t: Traverse data in the hash table.    |\n");
    printf("|p: Put a data into the hash table.     |\n");
    printf("|d: Delete a data in the hash table.    |\n");
    printf("|s: Search a key in the hash table.     |\n");
    printf("|i: Init the hash table.                |\n");
    printf("|e: End this program.                   |\n\n");

    while(1)
    {
        printf("Enter a above command: ");
        scanf("%s", str);

        switch (*str)
        {
            case 'r':
                read_csvfile(ht);
                break;
            case 't':
                traverse_table(ht);
                break;
            case 'p':
                printf ("Enter a key you want to put: ");
                scanf("%s", key);
                printf ("Enter a record you want to put: ");
                scanf("%d", &rec);
                insert_hash(ht, key, rec);
                break;
            case 'd':
                printf ("Enter a key you want to delete: ");
                scanf("%s", key);
                delete_hash(ht, key);
                break;
            case 's':
                printf ("Enter a key you want to search: ");
                scanf("%s", key);
                rec = search_hash(ht, key, &err);
                if (rec >= 0)
                    printf("The record is %d.\n", rec);
                else
                    printf("Could not find the key.\n");
                break;
            case 'i':
                delete_hash_table(ht);
                ht = make_hash_table(TABLESIZE);
                break;
            case 'e':
                delete_hash_table(ht);
                return 0;
            default :
                printf("Could not find your command.\n");
                break;
        }

        printf("\n");
    }

    return 0;
}
