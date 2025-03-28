#ifndef SLL_H
#define SLL_H

#include <stddef.h>

#define ERR(msg) do { \
        fprintf(stderr, "error: %s at <%s:%d>\n", \
            msg, __FILE__, __LINE__); \
        exit(1); \
    } while (0)

typedef struct Node {
    int data;
    struct Node *next;
} Node;

#define INVALID_DATA -1

typedef struct SinglyLinkedList {
    Node dummy_head;
    size_t size;
} SinglyLinkedList;

SinglyLinkedList *sll_new();
void sll_destroy(SinglyLinkedList *sll);
void sll_insert(SinglyLinkedList *sll, int value);
void sll_delete(SinglyLinkedList *sll, int value);
Node *sll_search(SinglyLinkedList *sll, int value);
void sll_update(SinglyLinkedList *sll, int old_val, int new_val);
void sll_reverse(SinglyLinkedList *sll);
void sll_print(SinglyLinkedList *sll);

#endif /* SLL_H */