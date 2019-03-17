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

/* 木構造のために再帰的データ型の定義 */
struct tree {
    int key;
    struct tree *left, *right;
};
struct tree *tree(int n);

void print_tree(struct tree *t, int h);
void preorder(struct tree *t);
void inorder(struct tree *t);
void postorder(struct tree *t);
void process_node(struct tree *t); 

#define EOD -1
/* 初期データリスト */
int a[ ] = { 8, 9, 11, 15, 19, 20, 21, 7, 3, 2, 1, 5, 6, 4, 13, 14, 10, 12, 17, 16, 18, EOD};

int get_data(void);
int count_data(void);

int main(void)
{
    struct tree *root;

    /* 完全バランス木の生成 */
    root = tree( count_data( ) );
    /* 木構造の表示 */
    printf( "木構造:\n" );
    print_tree( root, 0 );
    /* 先順（preorder）の処理の例 */
    printf( "\n 先順でのノード処理:\n" );
    preorder( root );
    /* 中順（inorder）の処理の例 */
    printf("\n 中順でのノード処理:\n" );
    inorder( root );
    /* 後順（postorder）の処理の例 */
    printf( "\n 後順でのノード処理:\n" );
    postorder( root );
    printf( "\n" );
    return 0;
}

/* n 個のノードを持つ完全バランス木を生成する
* 各ノード内のデータは get_data( )により与えられるものとする */
struct tree * tree( int n )
{
    struct tree *newtree;
    int nl, nr;

    if ( n==0 )
        return( NULL );
    else {
        nl = n/2; nr = n-nl-1;
        /* 完全バランス木では左右の部分木の節点数の差は高々1 */
        newtree =(struct tree *)malloc( sizeof( struct tree ) );
        newtree->key = get_data( );
        newtree->left = tree( nl ); /* 再帰的に左部分木を生成 */
        newtree->right = tree( nr ); /* 再帰的に右部分木を生成 */
        return( newtree );
    }
}

/* 木を印刷する．h は根（root）から見た木の深さを表す．印刷する順番は，木構
* 造について，「右部分木」，「根（そのノード）」，「左部分木」．（中順と異なる）*/
void print_tree( struct tree *t, int h )
{
    int i;

    if ( t != NULL ) {
        print_tree( t->right, h+1 ); /* 右部分木を印刷 */
    for( i=0; i<h; i++ ) /* 木の深さの分だけ TAB(8 文字字下げ)を印刷 */
        printf( "\t" );
        printf( "%d\n", t->key ); /* そのノードのキーを印刷 */
        print_tree( t->left, h+1 ); /* 左部分木を印刷 */
    }
}

/* 先順の処理例 */
void preorder( struct tree *t )
{
    if ( t != NULL ) {
        process_node( t );
        preorder( t->left );
        preorder( t->right );
    }
}

/* 中順の処理例 */
void inorder( struct tree *t )
{
    if ( t != NULL ) {
        inorder( t->left );
        process_node( t );
        inorder( t->right );
    }
}

/* 後順の処理例 */
void postorder( struct tree *t )
{
    if ( t != NULL ) {
        postorder( t->left );
        postorder( t->right );
        process_node( t );
    }
}

/* ノードに対する処理．何でも良い．ここでは，キーの値を印刷している．*/
void process_node( struct tree *t )
{
    printf( "<%d> ", t->key );
}

/* データ数カウント */ 
int count_data( void )
{
    int i = 0;

    while( a[i] != EOD )
        i++;
        return i;
    }

/* データ取得 */
int get_data( void )
{
    static int i=0;
    return a[i++];
}
