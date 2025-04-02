#ifndef DLL_H
#define DLL_H

#include <stddef.h>

#define ERR(msg) do { \
        fprintf(stderr, "error: %s at <%s:%d>\n", \
            msg, __FILE__, __LINE__); \
        exit(1); \
    } while (0)

typedef struct Node {
    int data;
    struct Node *next;
    struct Node *prev;
} Node;

#define INVALID_DATA -2147483648

typedef struct DoublyLinkedList {
    Node dummy_head;
    Node dummy_tail;
    size_t size;
} DoublyLinkedList;

DoublyLinkedList *dll_new();
void dll_destroy(DoublyLinkedList *dll);
void dll_insert(DoublyLinkedList *dll, int value);
void dll_delete(DoublyLinkedList *dll, int value);
Node *dll_search(DoublyLinkedList *dll, int value);
void dll_update(DoublyLinkedList *dll, int old_val, int new_val);
void dll_reverse(DoublyLinkedList *dll);
void dll_print(DoublyLinkedList *dll, int flag);

#endif /* DLL_H */