#ifndef MY_LIST_H
#define MY_LIST_H
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Node {
    int val;
    struct Node *next;
} Node;

typedef struct List {
    Node *head;
} List;

size_t size(List *list);
Node **find_node(List *list, Node *before);
void insert_before(List *list, Node *before, Node *target);    //insert before
void remove_naive(List *list, Node *target);
void remove_better(List *list, Node *target);

void make_test();

#ifdef __cplusplus
}
#endif

#endif  /* MY_LIST_H */