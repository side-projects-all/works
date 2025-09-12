#ifndef T_LIST_H
#define T_LIST_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdint.h>

// use gcc, then you have typeof, then you can have compile time type security
#if defined(__GNUC__)
#define __LIST_HAVE_TYPEOF 1
#endif

#ifndef container_of
#ifdef __LIST_HAVE_TYPEOF
#define container_of(ptr, type, member)                            \
    __extension__({                                                \
        const __typeof__(((type *) 0)->member) *__pmember = (ptr); \
        (type *) ((char *) __pmember - offsetof(type, member));    \
    })
#else
#define container_of(ptr, type, member) \
    ((type *) ((char *) (ptr) - offsetof(type, member)))
#endif
#endif

struct list_head {
    struct list_head *prev;
    struct list_head *next;
};

// no need to add semicolon for macro
#define LIST_HEAD(head) struct list_head head = {&(head), &(head)}

static inline void INIT_LIST_HEAD(struct list_head *head)
{
    head->next = head;
    head->prev = head;
}

static inline void list_add(struct list_head *node, struct list_head *head)
{
    struct list_head *next = head->next;

    next->prev = node;
    node->next = next;
    node->prev = head;
    head->next = node;
}

static inline void list_add_tail(struct list_head *node, struct list_head *head)
{
    struct list_head *prev = head->prev;
    prev->next = node;
    node->next = head;
    node->prev = prev;
    head->prev = node;
}

static inline void list_del(struct list_head *node)
{
    struct list_head *next = node->next;
    struct list_head *prev = node->prev;

    next->prev = prev;
    prev->next = next;

#ifdef LIST_POISIONING
    node->prev = (struct list_head *) (0x00100100);
    node->next = (struct list_head *) (0x00200200);
#endif
}

static inline void list_del_init(struct list_head *node)
{
    list_del(node);
    INIT_LIST_HEAD(node);
}

static inline int list_empty(const struct list_head *head)
{
    return (head->next == head);
}

static inline int list_is_singular(const struct list_head *head)
{
    return (!list_empty(head) && head->prev == head->next);
}

static inline void list_splice(struct list_head *list, struct list_head *head)
{
    struct list_head *head_first = head->next;
    struct list_head *list_first = list->next;
    struct list_head *list_last = list->prev;

    if (list_empty(list))
        return;

    head->next = list_first;
    list_first->prev = head;

    list_last->next = head_first;
    head_first->prev = list_last;
}

static inline void list_splice_tail(struct list_head *list,
                                    struct list_head *head)
{
    struct list_head *head_last = head->prev;
    struct list_head *list_first = list->next;
    struct list_head *list_last = list->prev;

    if (list_empty(list))
        return;

    head->prev = list_last;
    list_last->next = head;
    list_first->prev = head_last;
    head_last->next = list_first;
}

static inline void list_splice_init(struct list_head *list,
                                    struct list_head *head)
{
    list_splice(list, head);
    INIT_LIST_HEAD(list);
}

static inline void list_splice_tail_init(struct list_head *list,
                                         struct list_head *head)
{
    list_splice_tail(list, head);
    INIT_LIST_HEAD(list);
}

static inline void list_cut_position(struct list_head *head_to,
                                     struct list_head *head_from,
                                     struct list_head *node)
{
    struct list_head *head_from_first = head_from->next;

    if (list_empty(head_from))
        return;

    if (head_from == node) {
        INIT_LIST_HEAD(head_to);
        return;
    }

    head_from->next = node->next;
    head_from->next->prev = head_from;

    head_to->prev = node;
    node->next = head_to;
    head_to->next = head_from_first;
    head_to->next->prev = head_to;
}

static inline void list_move(struct list_head *node, struct list_head *head)
{
    list_del(node);
    list_add(node, head);
}

static inline void list_move_tail(struct list_head *node,
                                  struct list_head *head)
{
    list_del(node);
    list_add_tail(node, head);
}

#define list_entry(node, type, member) container_of(node, type, member)

#define list_first_entry(head, type, member) \
    list_entry((head)->next, type, member)

#define list_last_entry(head, type, member) \
    list_entry((head)->prev, type, member)

#define list_for_each(node, head) \
    for (node = (head)->next; node != (head); node = node->next)

#ifdef __LIST_HAVE_TYPEOF
#define list_for_each_entry(entry, head, member)                       \
    for (entry = list_entry((head)->next, __typeof__(*entry), member); \
         &entry->member != (head);                                     \
         entry = list_entry(entry->member.next, __typeof__(*entry), member))
#endif

#define list_for_each_safe(node, safe, head)                     \
    for (node = (head)->next, safe = node->next; node != (head); \
         node = safe, safe = node->next)

#define list_for_each_entry_safe(entry, safe, head, member)                \
    for (entry = list_entry((head)->next, __typeof__(*entry), member),     \
        safe = list_entry(entry->member.next, __typeof__(*entry), member); \
         &entry->member != (head); entry = safe,                           \
        safe = list_entry(safe->member.next, __typeof__(*entry), member))

// for not expanding any macro with the same name!
#undef __LIST_HAVE_TYPEOF

void make_test();

#define ARRAY_SIZE(x) (sizeof(x) / sizeof(x[0]))

struct list_node {
    uint16_t i;
    struct list_head link;
};

#ifdef __cplusplus
}
#endif

#endif /* T_LIST_H */