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
Input sample: 
55, 62, 89, 85, 97, 56, 71, 82, 38, 49, 25, 67, 58, 92, 100, 44, 69, 72, 65, 
52, 41, 84, 21, 60, 95, 12, 35, 42, 105, 99, 34, 47, 35, 79, 95, 50, 25, 51
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
    int result;    // 数値の大小比較結果

    // ノードが存在しない場合
    if ((*node) == NULL) {

        // 新しい領域を割り当てノードを作成する
        (*node) = malloc(sizeof(struct node));
        if ((*node) == NULL){
            fprintf(stderr, "NULL");
            exit (8);
        }

        // メンバを初期化
        (*node)->left_ptr  = NULL;
        (*node)->right_ptr = NULL;
        (*node)->value     = value;

        // make_tree関数を終了
        return;
    }

    // テキストから取り出した数値をノードの数値と比較
    // 現在のノードより大きかったら正。小さかったら負。等しかったら0
    if ((*node)->value < value) {
        result = 1;
    } else if ((*node)->value > value) {
        result = -1;
    } else if ((*node)->value == value) {
        result = 0;
    }

    // 現在の数値が既にあれば、新たなノードは作成せずmake_tree関数を終了
    if (result == 0)
        return;

    // 大きかったら右枝に移動
    if (0 < result) {
        make_tree(&(*node)->right_ptr, value);
    }
    // 小さかったら左枝に移動
    else {
        make_tree(&(*node)->left_ptr, value);
    }
}

void read_csvfile(BinaryTree *tree)
{
    FILE *lf;
    char bff[1000];
    char *value_a;

    /* file open */
    if(!(lf=fopen("input.csv","r"))){
        printf("File open error.\n");
    }

    /* read data */
    fgets(bff, 1000, lf);
    for(value_a=strtok(bff, ","); value_a!=NULL; value_a=strtok(NULL, ",")) {
        make_tree(&(*tree), atoi(value_a));
    }

    /* file close */
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

/* 最小の値をもつ節を削除する */
BinaryTree delete_min(BinaryTree* p)
{
    BinaryTree x;


    /* 最小の値を持った要素は、必ず左の子を辿った先にある */
    while( (*p)->left_ptr != NULL ){
        p = &(*p)->left_ptr;
    }

    x = *p;            /* x が削除される要素 */
    *p = (*p)->right_ptr;  /* x の右の子を x の位置へ移動させる (right が NULL でも構わない) */

    return x;
}

/* 二分探索木から要素を取り除く */
int bsearch_tree_remove(BinaryTree* tree, int value)
{
    BinaryTree* p = tree;
    BinaryTree x;

    while( *p != NULL ){
        x = *p;

        if( x->value == value ){
            if( x->left_ptr == NULL && x->right_ptr == NULL ){
                /* 取り除かれる要素が葉であれば、子がいないので問題なく削除できる */
                *p = NULL;
            }
            else if( x->left_ptr == NULL ){
                /* 右の子があるなら、取り除かれる要素の位置へ移動させる */
                *p = x->right_ptr;
            }
            else if( x->right_ptr == NULL ){
                /* 左の子があるなら、取り除かれる要素の位置へ移動させる */
                *p = x->left_ptr;
            }
            else{
                /* 左右に子があるなら、左部分木の中で一番大きい値を持った要素か、
                   右部分木の中で一番小さい値を持った要素のいずれかを、
                   取り除かれる要素の位置へ移動させる。
                   ここでは、右部分木の中で一番小さい値を移動させている。
                */
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

void traverse(BinaryTree tree)
{
    printf("pre_order\n");
    pre_order(tree);
    printf("\n\n");

    printf("in_order\n");
    in_order(tree);
    printf("\n\n");

    printf("post_order\n");
    post_order(tree);
    printf("\n\n");
}

int main()
{
    BinaryTree tree = NULL;

    read_csvfile(&tree);
    traverse(tree);

    bsearch_tree_remove(&tree, 89);
    traverse(tree);

    return 0;
}