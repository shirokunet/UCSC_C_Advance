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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct node {
    int     value;
    struct  node* left_ptr;
    struct  node* right_ptr;
};
typedef struct node* BinaryTree;


void make_tree(BinaryTree *node, int value)
{
    int result;

    // No more nodes.
    if ((*node) == NULL) {

        // Make a new node.
        (*node) = malloc(sizeof(struct node));
        if ((*node) == NULL){
            fprintf(stderr, "NULL");
            exit (8);
        }

        // Init members.
        (*node)->left_ptr  = NULL;
        (*node)->right_ptr = NULL;
        (*node)->value     = value;

        // End make_tree function.
        return;
    }

    // Compare a value and a current node.
    // If is the value higher than the current node, a result is 1.
    // If is the value lower than the current node, a result is -1.
    // If is the value same as the current node, a result is 0.
    if ((*node)->value < value) {
        result = 1;
    } else if ((*node)->value > value) {
        result = -1;
    } else if ((*node)->value == value) {
        result = 0;
    }

    // If find same value in the tree, end this function,
    if (result == 0)
        return;

    // Move to right node.
    if (0 < result) {
        make_tree(&(*node)->right_ptr, value);
    }
    // Move to left node.
    else {
        make_tree(&(*node)->left_ptr, value);
    }
}

void read_csvfile(BinaryTree *tree)
{
    FILE *lf;
    char bff[1000];
    char *value_a;

    if(!(lf=fopen("input.csv","r"))){
        printf("File open error.\n");
    }

    fgets(bff, 1000, lf);
    for(value_a=strtok(bff, ","); value_a!=NULL; value_a=strtok(NULL, ",")) {
        make_tree(&(*tree), atoi(value_a));
    }

    fclose(lf);
}

void pre_order(BinaryTree tree)
{
    if(tree == NULL)
        return;

    printf("%d,", tree->value);
    pre_order(tree->left_ptr);
    pre_order(tree->right_ptr);
}

void in_order(BinaryTree tree)
{
    if(tree == NULL)
        return;

    in_order(tree->left_ptr);
    printf("%d,", tree->value);
    in_order(tree->right_ptr);
}

void post_order(BinaryTree tree)
{
    if(tree == NULL)
        return;

    post_order(tree->left_ptr);
    post_order(tree->right_ptr);
    printf("%d,", tree->value);
}

void traverse(BinaryTree tree)
{
    printf("[Pre Order]  ");
    pre_order(tree);
    printf("\n");

    printf("[In Order]   ");
    in_order(tree);
    printf("\n");

    printf("[Post Order] ");
    post_order(tree);
    printf("\n\n");
}

/* Delete the node it has minimum value. */
BinaryTree delete_min(BinaryTree* p)
{
    BinaryTree x;

    /* The node it has minimum value should be most left position. */
    while( (*p)->left_ptr != NULL ){
        p = &(*p)->left_ptr;
    }

    x = *p;            /* x should be deleted */
    *p = (*p)->right_ptr;  /* The node on the right side of x move to the position of x. (even right is NULL) */

    return x;
}

/* Removed a node from a tree. */
int tree_delete(BinaryTree* tree, int value)
{
    BinaryTree* p = tree;
    BinaryTree x;

    while( *p != NULL ){
        x = *p;

        if( x->value == value ){
            if( x->left_ptr == NULL && x->right_ptr == NULL ){
                /* If the node is leaf. */
                *p = NULL;
            }
            else if( x->left_ptr == NULL ){
                /* If it has right chlid. */
                *p = x->right_ptr;
            }
            else if( x->right_ptr == NULL ){
                /* If it has left chlid. */
                *p = x->left_ptr;
            }
            else{
                /* If it has left chlid and right child. */
                *p = delete_min( &x->right_ptr );
                (*p)->left_ptr = x->left_ptr;
                (*p)->right_ptr = x->right_ptr;
            }

            free( x );
            return 1;
        }
        else if( x->value < value ){
            p = &x->right_ptr;
        }
        else{
            p = &x->left_ptr;
        }
    }

    return 0;
}

void delete_userinput(BinaryTree* tree)
{
    int delete_value = 0;

    printf ("Enter a value you want to delete: "); 
    scanf("%d", &delete_value);
    tree_delete(&(*tree), delete_value);
    printf("\n");
}

void tree_search(BinaryTree tree, int value)
{
    BinaryTree p = tree;

    while( p != NULL ){
        if( p->value == value ){
            printf(" %d\tFound!\n", value);
            return;
        }
        else if( p->value < value ){
            p = p->right_ptr;
        }
        else{
            p = p->left_ptr;
        }
    }

    printf(" %d\tCould not find...\n", value);
    return;
}

void search_userinput(BinaryTree tree)
{
    char str[500];
    char *token;

    printf ("Enter a array of value you want to serch: "); 
    scanf("%s", str);
    for(token=strtok(str, ","); token!=NULL; token=strtok(NULL, ",")) {
        tree_search(tree, atoi(token));
    }
    printf("\n");
}

int main()
{
    BinaryTree tree = NULL;
    char str[256];

    read_csvfile(&tree);

    while(1)
    {
        printf("|t: Traverse nodes in the tree.          |\n");
        printf("|d: Delete a node in the tree.           |\n");
        printf("|s: Serch an array of value in the tree. |\n");
        printf("|e: End this program.                    |\n\n");

        printf("Enter a above command: ");
        scanf("%s", str);

        if (strcmp(str,"t") == 0)
            traverse(tree);
        else if (strcmp(str,"d") == 0)
            delete_userinput(&tree);
        else if (strcmp(str,"s") == 0)
            search_userinput(tree);
        else if (strcmp(str,"e") == 0)
            break;
        else
            printf("Could not find your command.\n\n");
    }

    return 0;
}