
#ifndef LIST_QSORT_H
#define LIST_QSORT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "t_list.h"
#include "t_util.h"

static void list_qsort_rec(struct list_head *head) {
    struct list_head list_less;
    struct list_head list_greater;

    struct list_node *pivot;
    struct list_node *node = NULL;
    struct list_node *is = NULL;

    if (list_empty(head) || list_is_singular(head)) return;

    INIT_LIST_HEAD(&list_less);
    INIT_LIST_HEAD(&list_greater);

    pivot = list_first_entry(head, struct list_node, link);
    list_del(&pivot->link);

    list_for_each_entry_safe(node, is, head, link) {
        if (cmpint(&node->i, &pivot->i) < 0) {
            list_move_tail(&node->link, &list_less);
        } else {
            list_move_tail(&node->link, &list_greater);
        }
    }

    list_qsort_rec(&list_less);
    list_qsort_rec(&list_greater);

    list_add(&pivot->link, head);
    list_splice(&list_less, head);
    list_splice_tail(&list_greater, head);
}
static void list_qsort_iter(struct list_head *head) {
    #define MAX_LEVEL 300
    struct list_node *beg[MAX_LEVEL];
    struct list_node *end[MAX_LEVEL];
    struct list_node *L;
    struct list_node *R;
    struct list_node piv;   //this is a copy
    int i = 0;

    beg[0] = list_first_entry(head, struct list_node, link);
    end[0] = list_last_entry(head, struct list_node, link);

    while (i >= 0) {
        L = beg[i];
        R = end[i];
    
        if (L != R && &beg[i]->link != head) {
            piv = *beg[i];
            if (i == MAX_LEVEL - 1) {
                assert(-1);
                return;
            }

            while (L != R) {

                while (R->i >= piv.i && L != R) {
                    R = list_entry(R->link.prev, struct list_node, link);
                }

                if (L != R) {
                    L->i = R->i;
                    L = list_entry(L->link.next, struct list_node, link);
                }

                while (L->i <= piv.i && L != R) {
                    L = list_entry(L->link.next, struct list_node, link);
                }

                if (L != R) {
                    R->i = L->i;
                    R = list_entry(R->link.prev, struct list_node, link);
                }
            }

            L->i = piv.i;
            beg[i + 1] = list_entry(L->link.next, struct list_node, link);  //this is right part begin
            end[i + 1] = end[i];                                            //this is right part end
            end[i++] = L;   //it becomes left part end and increases the index

        } else {
            --i;
        }
    }
}

#ifdef __cplusplus
}
#endif

#endif /* LIST_QSORT_H */ 