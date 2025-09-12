#include "single_linked_list.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void add_at_begin(s_node **head, int new_val) {
    s_node *new_node = malloc(sizeof(s_node));
    assert(new_node);

    s_node **pptr = head;
    s_node *tmp = *head;
    new_node->val = new_val;
    new_node->next = tmp;

    *head = new_node;
}
void add_at_tail(s_node **head, int new_val) {
    
    s_node *new_node = malloc(sizeof(s_node));
    assert(new_node);

    s_node **pptr = head;
    new_node->val = new_val;
    new_node->next = NULL;

    while (*pptr) {
        pptr = &(*pptr)->next;
    }

    *pptr = new_node;
}

s_node *find_entry(s_node *head, int val) {

    if (!head) return NULL;
    s_node *ptr = head;

    for (; ptr && ptr->val != val; ptr = ptr->next)

    return ptr;
}

void remove_entry(s_node **head, s_node *entry) {
    if (!head) return;

    s_node **pptr = head;

    while ((*pptr) != entry) {
        pptr = &(*pptr)->next;
    }

    *pptr = entry->next;
    free(entry);
}

void del_list(s_node **head) {

    while (*head) {
        s_node *next = (*head)->next;
        free(*head);
        *head = next;
    }
}

void swap_pair(s_node **head) {

    for (; *head && (*head)->next; head = &(*head)->next->next) {
        s_node *tmp = *head;
        *head = (*head)->next;
        tmp->next = (*head)->next;
        (*head)->next = tmp;
    }
}

void swap_pair_by_val(s_node **head) {
    for (; *head && (*head)->next; head = &(*head)->next->next) {
        XOR_SWAP_UNSAFE((*head)->val, (*head)->next->val);
    }
}

void reverse(s_node **head) {
    if (!head) return;

    s_node *prev = NULL;
    s_node *next_node = (*head)->next;
    (*head)->next = prev;

    while (next_node) {
        prev = (*head);
        *head = next_node;
        next_node = next_node->next;
        (*head)->next = prev;
    }
}

void recursive_rev(s_node **head) {
    if (!head) return;


}

void recursive_rev_step(s_node *curr, s_node *prev, s_node **head) {

    s_node *next_node = curr->next;
    curr->next = prev;

    if (!next_node) {
        *head = curr;
        return;
    }

    recursive_rev_step(next_node, curr, head);
}

void shuffle(s_node **head) {
    srand(time(NULL));

    //get length
    int len = 0;
    s_node **pptr = head;
    while (*pptr) {
        ++len;
        pptr = &(*pptr)->next;
    }

    //append shuffle result to another linked list
    s_node *new_list = NULL; 
    s_node **new_head = &new_list;
    s_node **new_tail = &new_list;

    while (len) {
        int ran = rand() % len;
        pptr = head;

        //move to tail
        while (ran--) {
            pptr = &(*pptr)->next;
        }

        s_node *tmp = *pptr;
        *pptr = (*pptr)->next;

        tmp->next = NULL;
        if (new_list) {
            (*new_tail)->next = tmp;
            new_tail = &(*new_tail)->next;

        } else {
            new_list = tmp;
        }

        --len;
    }

    *head = *new_head;
}

void print_list(s_node *head) {
    for (s_node *curr = head; curr; curr = curr->next) {
        printf("%d ", curr->val);
    }
    printf("\n");
}

void single_linked_list_test() {

    s_node *head = NULL;
    for (int i = 1; i <= 10; ++i) {
        //add_at_tail(&head, i);
        add_at_begin(&head, i);
    }
    
    print_list(head);
    shuffle(&head);
    print_list(head);

    del_list(&head);
}