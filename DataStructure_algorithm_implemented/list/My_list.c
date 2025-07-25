#include "My_list.h"

size_t size(List *l) {
    size_t k = 0;
    Node *curr = l->head;
    while (curr) {
        curr = curr->next;
        ++k;
    }

    return k;
}

Node **find_node(List *l, int val) {

    Node **curr = &l->head;
    while (*curr != NULL && (*curr)->val != val) {
        curr = &(*curr)->next;
    }

    return curr;
}

void remove_naive(List *l, Node *target) {
    Node *prev = NULL;
    Node *curr = l->head;
    while (curr != target) {
        prev = curr;
        curr = curr->next;
    }

    if (prev) 
        prev->next = curr->next;
    else
        l->head = curr->next;       //for test case: remove head
}

void remove_better(List *l, Node *target) {
    Node **indirect = &l->head;
    while (*indirect != target) {
        indirect = &(*indirect)->next;
    }

    *indirect = target->next;
}

void insert_before(List *l, Node *before, Node *target) {

    Node **indirect = find_node(l, before->val);
    *indirect = target;
    target->next = before;
}

void make_test() {
    Node nodes[10];
    List l;
    for (size_t i = 0; i < 10; ++i) {
        nodes[i].val = i;
        nodes[i].next = NULL;
    }
    l.head = NULL;

    for (size_t i = 0; i < 10; ++i) {
        insert_before(&l, l.head, &nodes[i]);
    }
    
    //insert at the end of the list
    insert_before(&l, NULL, &nodes[5]);

    remove_better(&l, &nodes[7]);
}