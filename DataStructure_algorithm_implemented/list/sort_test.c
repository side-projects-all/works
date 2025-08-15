#include "sort_test.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "t_list.h"
#include "list_insertion_sort.h"
#include "list_qsort.h"
#include "list_msort.h"


void create_list2(struct list_head *head, struct list_node *node, struct list_node *is, size_t* len) {
    //int arr[10] = {4, 2, 3, 4, 5, 6, 4, 7, 6, 9};
    //int arr[5] = {2, 5, 7, 9, 13};
    int arr[3] = {2, 5, 7};
    *len = ARRAY_SIZE(arr);

    for (size_t i = 0; i < *len; ++i) {
        node = (struct list_node *) malloc(sizeof(*node));
        assert(node);
        node->i = arr[i];
        list_add_tail(&node->link, head);
    }

    node = NULL;
    is = NULL;
}

void create_list(struct list_head *head, struct list_node *node, struct list_node *is, size_t* len) {
    int arr[10] = {4, 2, 3, 4, 5, 6, 4, 7, 6, 9};
    //int arr[5] = {1, 3, 6, 8, 12};
    //int arr[6] = {8, 12, 5, 1, 6, 4};
    *len = ARRAY_SIZE(arr);

    for (size_t i = 0; i < *len; ++i) {
        node = (struct list_node *) malloc(sizeof(*node));
        assert(node);
        node->i = arr[i];
        list_add_tail(&node->link, head);
    }

    node = NULL;
    is = NULL;
}
void print_list(struct list_head *head, struct list_node *node, struct list_node *is) {

    list_for_each_entry_safe(node, is, head, link) {
        printf("%d, ", node->i);
    }
    printf("\n");
}

void free_list(struct list_head *head, struct list_node *node, struct list_node *is, int arr_len) {
    int i = 0;
    list_for_each_entry_safe(node, is, head, link) {
        list_del(&node->link);
        free(node);
        ++i;
    }
    assert(i == arr_len);
    assert(list_empty(head));
}

void insertion_sort_test() {
    size_t len = 0;
    struct list_head head;
    struct list_node *node = NULL;
    struct list_node *is = NULL;

    INIT_LIST_HEAD(&head);
    assert(list_empty(&head));

    create_list(&head, node, is, &len);

    assert(!list_empty(&head));

    printf("before insertion sort\n");
    print_list(&head, node, is);

    list_insertion_sort(&head);

    printf("after insertion sort\n");
    print_list(&head, node, is);

    free_list(&head, node, is, len);
}
void quick_sort_rec_test() {
    size_t len = 0;
    struct list_head head;
    struct list_node *node = NULL;
    struct list_node *is = NULL;

    INIT_LIST_HEAD(&head);
    assert(list_empty(&head));

    create_list(&head, node, is, &len);

    assert(!list_empty(&head));

    printf("before qucik sort\n");
    print_list(&head, node, is);

    list_qsort_rec(&head);

    printf("after quick sort\n");
    print_list(&head, node, is);

    free_list(&head, node, is, len);
}

void quick_sort_iter_test() {
    size_t len = 0;
    struct list_head head;
    struct list_node *node = NULL;
    struct list_node *is = NULL;

    INIT_LIST_HEAD(&head);
    assert(list_empty(&head));

    create_list(&head, node, is, &len);

    assert(!list_empty(&head));

    printf("before qucik sort\n");
    print_list(&head, node, is);

    list_qsort_iter(&head);

    printf("after quick sort\n");
    print_list(&head, node, is);

    free_list(&head, node, is, len);
}

void merge_test() {
    size_t len = 0;
    struct list_head head1;
    struct list_node *node = NULL;
    struct list_node *is = NULL;

    //for list1
    INIT_LIST_HEAD(&head1);
    assert(list_empty(&head1));

    create_list(&head1, node, is, &len);

    assert(!list_empty(&head1));
    print_list(&head1, node, is);

    //for list2
    struct list_head head2;
    INIT_LIST_HEAD(&head2);
    assert(list_empty(&head2));

    create_list2(&head2, node, is, &len);

    assert(!list_empty(&head2));
    print_list(&head2, node, is);

    printf("before merge\n");
    head1 = merge_2_list(&head1, &head2);
    list_splice_tail_init(&head1, &head2);  //this is necessary. Without this operation, the last node->next will point to wrong address
    printf("after merge\n");

    print_list(&head2, node, is);
    free_list(&head2, node, is, len * 2);
}

void merge_sort_rec_test() {
    size_t len = 0;
    struct list_head head;
    struct list_node *node = NULL;
    struct list_node *is = NULL;

    INIT_LIST_HEAD(&head);
    assert(list_empty(&head));

    create_list(&head, node, is, &len);
    
    assert(!list_empty(&head));

    printf("before merge sort\n");
    print_list(&head, node, is);
    
    struct list_head tmp = list_msort_rec(&head);
    struct list_head head3;
    INIT_LIST_HEAD(&head3);
    list_splice_tail_init(&tmp, &head3);

    printf("after merge sort\n");
    print_list(&head3, node, is);

    free_list(&head3, node, is, len);
}

void merge_sort_iter_test() {
    size_t len = 0;
    struct list_head head;
    struct list_node *node = NULL;
    struct list_node *is = NULL;

    INIT_LIST_HEAD(&head);
    assert(list_empty(&head));

    create_list(&head, node, is, &len);
    
    assert(!list_empty(&head));

    printf("before merge sort\n");
    print_list(&head, node, is);
    
    list_msort_iter(&head);

    printf("after merge sort\n");
    print_list(&head, node, is);

    free_list(&head, node, is, len);
}