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
#include <stdbool.h>
#include <time.h>

// 連結リスト
typedef struct cell {
  char *key;
  int  value;
  struct cell *next;
} Cell;

// ハッシュ表
typedef struct {
  int size, count;
  Cell **table;
} HashTable;

// セルの生成
Cell *make_cell(const char *key, int val, Cell *next)
{
  Cell *cp = malloc(sizeof(Cell));
  if (cp != NULL) {
    cp->key = malloc(strlen(key) + 1);
    if (cp->key == NULL) {
      free(cp);
      return NULL;
    }
    strcpy(cp->key, key);
    cp->value = val;
    cp->next = next;
  }
  return cp;
}

// セルの廃棄
void delete_cell(Cell *cp)
{
  while (cp != NULL) {
    Cell *xs = cp->next;
    free(cp->key);
    free(cp);
    cp = xs;
  }
}

// ハッシュ表の生成
HashTable *make_hash_table(int size)
{
  HashTable *ht = malloc(sizeof(HashTable));
  if (ht != NULL) {
    ht->size = size;
    ht->count = 0;
    ht->table = malloc(sizeof(Cell *) * size);
    if (ht->table == NULL) {
      free(ht);
      return NULL;
    }
    // 初期化
    for (int i = 0; i < size; i++) ht->table[i] = NULL;
  }
  return ht;
}

// ハッシュ表の廃棄
void delete_hash_table(HashTable *ht)
{
  for (int i = 0; i < ht->size; i++)
    delete_cell(ht->table[i]);
  free(ht);
}

// ハッシュ関数
int hash_func(HashTable *ht, const char *key)
{
  unsigned int value = 0;
  for (; *key != '\0'; key++)
    value = (value << 3) + *key;
  return value % ht->size;
}

// 作業用関数
Cell *search_cell(HashTable *ht, const char *key, int hval)
{
  Cell *cp = ht->table[hval];
  for (; cp != NULL; cp = cp->next) {
    if (strcmp(cp->key, key) == 0) {
      return cp;
    }
  }
  return NULL;
}

// 探索
int search_hash(HashTable *ht, const char *key, bool *err)
{
  Cell *cp = search_cell(ht, key, hash_func(ht, key));
  if (cp != NULL) {
    *err = true;
    return cp->value;
  }
  *err = false;
  return 0;
}

// 挿入
bool insert_hash(HashTable *ht, const char *key, int val)
{
  int hval = hash_func(ht, key);
  Cell *cp = search_cell(ht, key, hval);
  if (cp == NULL) {
    // 先頭に追加
    ht->table[hval] = make_cell(key, val, ht->table[hval]);
    ht->count++;
    return true;
  } else {
    // 値を書き換える
    cp->value = val;
    return false;
  }
}

// 削除
bool delete_hash(HashTable *ht, const char *key)
{
  int hval = hash_func(ht, key);
  Cell *cp = ht->table[hval];
  if (cp != NULL) {
    if (strcmp(cp->key, key) == 0) {
      // 先頭データを削除
      ht->table[hval] = cp->next;
      ht->count--;
      free(cp->key);
      free(cp);
      return true;
    } else {
      // リストの途中から削除
      for (; cp->next != NULL; cp = cp->next) {
        if (strcmp(cp->next->key, key) == 0) {
          Cell *del = cp->next;
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

// 巡回
void foreach_hash(void (*func)(const char *, int), HashTable *ht)
{
  for (int i = 0; i < ht->size; i++) {
    for (Cell *cp = ht->table[i]; cp != NULL; cp = cp->next)
      func(cp->key, cp->value);
  }
}

// ハッシュは空か
bool is_empty_hash(HashTable *ht)
{
  return ht->count == 0;
}

// 要素数を返す
int length_hash(HashTable *ht)
{
  return ht->count;
}

// ハッシュを空にする
void clear_hash(HashTable *ht)
{
  ht->count =0;
  for (int i = 0; i < ht->size; i++) {
    delete_cell(ht->table[i]);
    ht->table[i] = NULL;
  }
}

//
// 二分探索木
//

// 節の定義
typedef struct node {
  char *key;
  int value;
  struct node *left;
  struct node *right;
} Node;

// 節の生成
Node *make_node(const char *key, int val)
{
  Node *node = malloc(sizeof(Node));
  if (node != NULL) {
    node->key = malloc(strlen(key) + 1);
    if (node->key == NULL) {
      free(node);
      return NULL;
    }
    strcpy(node->key, key);
    node->value = val;
    node->left = NULL;
    node->right = NULL;
  }
  return node;
}

// 探索
int search_node(const char *key, Node *node, bool *err)
{
  while (node != NULL) {
    int r = strcmp(key, node->key);
    if (r == 0) {
      *err = true;
      return node->value;
    } else if (r < 0)
      node = node->left;
    else
      node = node->right;
  }
  *err = false;
  return 0;
}

// 挿入
Node *insert_node(const char *key, int val, Node *node)
{
  if (node == NULL)
    return make_node(key, val);
  else {
    int r = strcmp(key, node->key);
    if (r < 0)
      node->left = insert_node(key, val, node->left);
    else if (r > 0)
      node->right = insert_node(key, val, node->right);
    return node;
  }
}

// 簡単なテスト
void test1(void)
{
  char buff[8][12];
  HashTable *ht = make_hash_table(5);
  bool err;
  printf("-- %d, %d --\n", is_empty_hash(ht), length_hash(ht));
  printf("----- insert -----\n");
  for (int i = 0; i < 8; i++) {
    sprintf(buff[i], "%d", rand());
    printf("%s, %d\n", buff[i], insert_hash(ht, buff[i], i));
  }
  printf("-- %d, %d --\n", is_empty_hash(ht), length_hash(ht));
  printf("------ search ------\n");
  for (int i = 0; i < 8; i++) 
    printf("%s, %d\n", buff[i], search_hash(ht, buff[i], &err)); 
  printf("------ delete ------\n");
  for (int i = 0; i < 8; i++) {
    printf("%s %d\n", buff[i], delete_hash(ht, buff[i]));
    int x = search_hash(ht, buff[i], &err);
    printf("%s, %d, %d\n", buff[i], x, err);
  } 
  printf("-- %d, %d --\n", is_empty_hash(ht), length_hash(ht));
  printf("----- delete hash -----\n");
  delete_hash_table(ht);
}

#define N 2500
char data[N][12];

// 線形探索
bool liner_search(const char *key, int size)
{
  for (int i = 0; i < size; i++) {
    if (strcmp(key, data[i]) == 0) return true;
  }
  return false;
}

void test2(int size)
{
  int i = 0;
  while (i < size) {
    sprintf(data[i], "%d", rand());
    if (!liner_search(data[i], i)) i++;
  }
}

// ハッシュ
void test3(int size)
{
  HashTable *ht = make_hash_table(99991);  // 10007 から変更
  bool err;
  char buff[12];
  while (length_hash(ht) < size) {
    sprintf(buff, "%d", rand());
    search_hash(ht, buff, &err);
    if (!err) insert_hash(ht, buff, 1);
  }
  delete_hash_table(ht);
}

// 二分探索木
void test4(int size)
{
  Node *root = NULL;
  int i = 0;
  char buff[12];
  bool err;
  while (i < size) {
    sprintf(buff, "%d", rand());
    search_node(buff, root, &err);
    if (!err) {
      root = insert_node(buff, i, root);
      i++;
    }
  }
}

int main(void)
{
  test1();
  /*
  for (int i = 100000; i <= N; i *= 2) {
    clock_t s = clock();
    test3(i);
    printf("%d, %.3f\n", i, (double)(clock() - s) / CLOCKS_PER_SEC);
  }
  */
  return 0;
}
