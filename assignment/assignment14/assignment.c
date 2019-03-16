/****************************************************
Prologue
University of California Extension, Santa Cruz
Advanced C Programming
Instructor: Rajainder A. Yeldandi
Author: Reyes
Assignment Number: 13
Topic: Binary Trees.
file name: assignment.c
Date: Mar 14, 2019
Objective: Practice.
Comments: None.
Input csv sample: 
55, 62, 89, 85, 97, 56, 71, 82, 38, 49, 25, 67, 58, 92, 100, 44, 69, 72, 65, 
52, 41, 84, 21, 60, 95, 12, 35, 42, 105, 99, 34, 47, 35, 79, 95, 50, 25, 51
Input sample for search: 71,51,38,5,0,25,42,91,35,47
****************************************************/

#include<stdio.h> 
#include<stdlib.h> 
#include <string.h>
#include <ctype.h>
 
/* Linked list node */
struct Node 
{ 
    int data; 
    struct Node* next; 
};

/* Function to create a new node with given data */
struct Node *newNode(int data) 
{ 
    struct Node *new_node = (struct Node *) malloc(sizeof(struct Node)); 
    new_node->data = data; 
    new_node->next = NULL; 
    return new_node; 
}

/* Function to insert a node at the beginning of the Singly Linked List */
void push(struct Node** head_ref, int new_data) 
{ 
    struct Node* new_node = newNode(new_data); 
    new_node->next = (*head_ref); 
    (*head_ref) = new_node; 
}

/* Adds contents of two linked lists and return the head node of resultant list */
struct Node* add_lists (struct Node* first, struct Node* second) 
{ 
    struct Node* res = NULL; // res is head node of the resultant list 
    struct Node *temp, *prev = NULL; 
    int carry = 0, sum; 
  
    while (first != NULL || second != NULL) //while both lists exist 
    { 
        // Calculate value of next digit in resultant list. 
        // The next digit is sum of following things 
        // (i)  Carry 
        // (ii) Next digit of first list (if there is a next digit) 
        // (ii) Next digit of second list (if there is a next digit) 
        sum = carry + (first? first->data: 0) + (second? second->data: 0); 
  
        // update carry for next calulation 
        carry = (sum >= 10)? 1 : 0; 
  
        // update sum if it is greater than 10 
        sum = sum % 10; 
  
        // Create a new node with sum as data 
        temp = newNode(sum); 
  
        // if this is the first node then set it as head of the resultant list 
        if(res == NULL) 
            res = temp; 
        else // If this is not the first node then connect it to the rest. 
            prev->next = temp; 
  
        // Set prev for next insertion 
        prev  = temp; 
  
        // Move first and second pointers to next nodes 
        if (first) first = first->next; 
        if (second) second = second->next; 
    } 
  
    if (carry > 0) 
      temp->next = newNode(carry); 
  
    // return head of the resultant list 
    return res; 
} 
  
// A utility function to print a linked list 
void print_list(struct Node *node) 
{ 
    while(node != NULL) 
    { 
        if (node->data)
            printf("%d", node->data); 
        node = node->next; 
    } 
    printf("\n"); 
}

void rev_string(char str[])
{
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len-i-1];
        str[len-i-1] = temp;
    }
}

int main()
{
    FILE *lf;
    char bff[1000];
    char *value_a;
    int len;
    char t[64];

    struct Node* res = NULL;
    struct Node* value_list[2] = {NULL};

    if(!(lf=fopen("input.csv","r"))){
        printf("File open error.\n");
    }

    for (int i = 0 ; i < 2 ; i++)
    {
        fgets(bff, 1000, lf);
        value_a = strtok(bff, "\n");
        len = strlen(value_a);
        printf("%d: %s\n", len, value_a);

        rev_string(value_a);

        for (int j = 0; j < len; ++j)
        {
            strncpy(t, value_a+j, 1);
            push(&value_list[i], atoi(t));
        }
        for (int j = 0; j < 50-len; ++j)
        {
            push(&value_list[i], 0);
        }
        print_list(value_list[i]);

        printf("\n");
    }
    fclose(lf);

    // Add the two lists and see result 
    res = add_lists(value_list[0], value_list[1]);
    printf("Resultant list is \n");
    print_list(res);
  
   return 0;
}