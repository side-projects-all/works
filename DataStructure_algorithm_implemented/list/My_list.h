#ifndef MY_LIST_H
#define MY_LIST_H
#include <stddef.h>

typedef struct Node {
    int val;
    struct Node *next;
} Node;

typedef struct List {
    Node *head;
} List;

size_t size(List *list);
Node **find_node(List *list, int val);
void insert_before(List *list, Node *before, Node *target);    //insert before
void remove_naive(List *list, Node *target);
void remove_better(List *list, Node *target);

void make_test();
#endif  /* MY_LIST_H */