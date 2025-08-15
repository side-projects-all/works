#ifndef LIST_MSORT_H
#define LIST_MSORT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "t_list.h"
#include "t_util.h"

static struct list_head merge_2_list(struct list_head *l1_head, struct list_head *l2_head) {
    
    struct list_head out;
    INIT_LIST_HEAD(&out);
    struct list_head *l1 = l1_head->next;
    struct list_head *l2 = l2_head->next;

    while (l1 != l1_head && l2 != l2_head) {
        struct list_node *e1 = list_entry(l1, struct list_node, link);
        struct list_node *e2 = list_entry(l2, struct list_node, link);

        if (e1->i <= e2->i) {
            struct list_head *n1 = l1->next;
            list_move_tail(l1, &out);
            l1 = n1;
        } else {
            struct list_head *n2 = l2->next;
            list_move_tail(l2, &out);
            l2 = n2;
        }
    }

    if (l1 != l1_head) list_splice_tail_init(l1_head, &out);
    if (l2 != l2_head) list_splice_tail_init(l2_head, &out);

    return out;   
}

static struct list_head list_msort_rec(struct list_head *head) {
    if (list_empty(head) || list_is_singular(head)) return *head;

    struct list_head *slow = head->next;
    struct list_head *fast;
    for (fast = slow->next->next; fast != head && fast->next != head; fast = fast->next->next) {
        slow = slow->next;
    }

    struct list_head first_part;               //left part include mid
    INIT_LIST_HEAD(&first_part);
    list_cut_position(&first_part, head, slow);  //right part after mid linked from head

    struct list_head left;
    INIT_LIST_HEAD(&left);
    struct list_head right;
    INIT_LIST_HEAD(&right);

    struct list_head left_sorted = list_msort_rec(&first_part);
    struct list_head right_sorted = list_msort_rec(head);
    list_splice_tail_init(&left_sorted, &left);
    list_splice_tail_init(&right_sorted, &right);

    return merge_2_list(&left, &right);
}

static struct list_head * merge_2_list_iter(struct list_head *l1, struct list_head *l2) {
    struct list_head *head;
    struct list_head **tail = &head;
    struct list_head **curr;

    while (l1 != NULL && l2 != NULL) {
        struct list_node *e1 = list_entry(l1, struct list_node, link);
        struct list_node *e2 = list_entry(l2, struct list_node, link);

        curr = (e1->i < e2->i) ? &l1 : &l2;
        *tail = *curr;

        tail = &(*tail)->next;  //point to the address of next pointer! Then you can splice next node directly
        *curr = (*curr)->next;
    }

    *tail = (l1 == NULL) ? l2 : l1;
    return head;
}

static void list_msort_iter(struct list_head *head) {
    if (list_empty(head) || list_is_singular(head)) return;

    //break circular
    head->prev->next = NULL;    //tail node next set null
    head->prev = head;          //head prev set to itself

    struct list_head *first = head->next;       //first node after head
    first->prev = NULL;                         //clear link
    head->next = head;

    int top = 0;
    int lists_len = 0;
    struct list_head *stack[300] = {NULL};
    struct list_head *lists[30000] = {NULL};
    stack[top] = first;

    while (top >= 0) {
        struct list_head *left = stack[top--];

        if (left) {
            struct list_head *slow = left;
            struct list_head *fast = slow->next;

            //find mid and disconnect prev pointer
            while (fast && fast->next) {
                slow->prev = NULL;
                slow = slow->next;
                fast->prev = NULL;
                fast = fast->next;
                fast->prev = NULL;
                fast = fast->next;
            }

            if (fast != NULL) fast->prev = NULL;
            struct list_head *right = slow->next;
            slow->next = NULL;

            stack[++top] = left;
            stack[++top] = right;
        } else {
            lists[lists_len++] = stack[top--];
        }
    }

    
    while (lists_len > 1) {
        for (int i = 0, j = lists_len - 1; i < j; ++i, --j) {
            lists[i] = merge_2_list_iter(lists[i], lists[j]);
        }

        lists_len = (lists_len + 1) / 2;
    }

    //reconnect prev
    struct list_head *prev_node = lists[0];
    struct list_head *next_node = prev_node->next;
    while (next_node != NULL) {
        next_node->prev = prev_node;
        next_node = next_node->next;
        prev_node = prev_node->next;
    }

    prev_node->next = head; //last node next point to head
    lists[0]->prev = head;  //first node prev point to head
    head->next = lists[0];  //head next point to first node
    head->prev = prev_node; //head prev point to last node
}

#ifdef __cplusplus
}
#endif

#endif /* LIST_MSORT_H */