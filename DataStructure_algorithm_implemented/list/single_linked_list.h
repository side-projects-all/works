
#ifndef SINGLE_LINKED_LIST_H
#define SINGLE_LINKED_LIST_H

#ifdef __cplusplus
extern "C" {
#endif

#define XOR_SWAP_UNSAFE(a, b) ((a) ^= (b), (b) ^= (a), (a) ^= (b))
#define XOR_SWAP (a, b) ((&(a) == &(b)) ? (a) : XOR_SWAP_UNSAFE(a, b))
        
typedef struct s_node {
    int val;
    struct s_node *next;
} s_node;

void add_at_begin(s_node **head, int new_val);
void add_at_tail(s_node **head, int new_val);
s_node *find_entry(s_node *head, int val);
void remove_entry(s_node **head, s_node *entry);
void del_list(s_node **head);
void swap_pair(s_node **head);
void swap_pair_by_val(s_node **head);
void reverse(s_node **head);
void recursive_rev(s_node **head);
void recursive_rev_step(s_node *curr, s_node *prev, s_node **head);
void shuffle(s_node **head);
void print_list(s_node *head);

void single_linked_list_test();

#ifdef __cplusplus
}
#endif

#endif  /* SINGLE_LINKED_LIST_H */