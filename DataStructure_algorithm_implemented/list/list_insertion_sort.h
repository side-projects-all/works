#ifndef LIST_INSERTION_SORT_H
#define LIST_INSERTION_SORT_H

#ifdef __cplusplus
extern "C" {
#endif
#include "t_list.h"
#include "t_util.h"

static void list_insert_sorted(struct list_node *entry, struct list_head *head) {
    struct list_node *node = NULL;
    
    if (list_empty(head)) {
        list_add(&entry->link, head);
        return;
    }

    list_for_each_entry(node, head, link) {
        if (cmpint(&entry->i, &node->i) < 0) {
            list_add_tail(&entry->link, &node->link);
            return;
        }
    }

    list_add_tail(&entry->link, head);
}

static void list_insertion_sort(struct list_head *head) {
    struct list_head list_unsorted;
    struct list_node *node = NULL;
    struct list_node *is = NULL;

    INIT_LIST_HEAD(&list_unsorted);
    list_splice_init(head, &list_unsorted);

    list_for_each_entry_safe(node, is, &list_unsorted, link) {
        list_del(&node->link);
        list_insert_sorted(node, head);
    }
}

#ifdef __cplusplus
}
#endif

#endif /* LIST_INSERTION_SORT_H */