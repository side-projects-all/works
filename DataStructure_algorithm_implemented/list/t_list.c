#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "t_list.h"

void make_test() {
    int arr[10] = {13, 2, 5, 3, 9, 7, 6, 4, 8, 1};
    struct list_head head;

    struct list_node *node = NULL;
    struct list_node *is = NULL;
    size_t i;

    INIT_LIST_HEAD(&head);
    assert(list_empty(&head));

    for (i = 0; i < ARRAY_SIZE(arr); ++i) {
        node = (struct list_node *) malloc(sizeof(*node));
        assert(node);
        node->i = arr[i];
        list_add_tail(&node->link, &head);
    }

    assert(!list_empty(&head));

    i = 0;
    list_for_each_entry_safe(node, is, &head, link) {
        list_del(&node->link);
        free(node);
        ++i;
    }

    assert(i == ARRAY_SIZE(arr));
    assert(list_empty(&head));
}