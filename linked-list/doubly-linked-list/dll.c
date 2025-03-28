#include "dll.h"
#include <stdio.h>
#include <stdlib.h>

DoublyLinkedList *dll_new()
{
    DoublyLinkedList *dll = malloc(sizeof(DoublyLinkedList));
    if (!dll) ERR("new singly linked list");

    dll->dummy_head = (Node) {
        .data = INVALID_DATA,
        .next = &dll->dummy_tail,
        .prev = NULL
    };
    dll->dummy_tail = (Node) {
        .data = INVALID_DATA,
        .next = NULL,
        .prev = &dll->dummy_head
    };
    dll->size = 0;

    return dll;
}

void dll_destroy(DoublyLinkedList *dll)
{
    Node *cur = dll->dummy_head.next, *next = NULL;
    while (cur != &dll->dummy_tail) {
        next = cur->next;
        free(cur);
        cur = next;
    }
    free(dll);
}

void dll_print(DoublyLinkedList *dll, int flag)
{
    Node *cur;

    if (flag == 0) {
        cur = dll->dummy_head.next;
        while (cur != &dll->dummy_tail) {
            printf(" %d", cur->data);
            cur = cur->next;
        }
    } else {
        cur = dll->dummy_tail.prev;
        while (cur != &dll->dummy_head) {
            printf(" %d", cur->data);
            cur = cur->prev;
        }
    }
    printf("\n");
}

void dll_insert(DoublyLinkedList *dll, int value)
{
    /* new a insert node */
    Node *node = malloc(sizeof(Node));
    if (!node) ERR("new a node");
    node->data = value;
    node->next = NULL;
    node->prev = NULL;

    /* find the insert position */
    Node *cur = dll->dummy_head.next, *prev = &dll->dummy_head;
    while (cur != &dll->dummy_tail) {
        if (cur->data > value) break;
        prev = cur;
        cur = cur->next;
    }

    /* insert (update the link)  */
    node->next = cur;
    cur->prev = node;
    prev->next = node;
    node->prev = prev;

    /* update the dll */
    (dll->size)++;
}

void dll_delete(DoublyLinkedList *dll, int value)
{
    /* find the delete position */
    Node *cur = dll->dummy_head.next, *prev = &dll->dummy_head;
    while (cur != &dll->dummy_tail) {
        if (cur->data == value) break;
        prev = cur;
        cur = cur->next;
    }

    /* find it */
    if (cur != &dll->dummy_tail) {
        /* delete (update the link) */
        prev->next = cur->next;
        cur->next->prev = prev;
        free(cur);

        /* update the dll */
        (dll->size)--;
    }
}

Node *dll_search(DoublyLinkedList *dll, int value)
{
    /* find the position */
    Node *cur = dll->dummy_head.next;
    while (cur != &dll->dummy_tail) {
        if (cur->data == value) break;
        cur = cur->next;
    }

    /* NULL -> not found */
    return (cur == &dll->dummy_tail) ? NULL : cur;
}

void dll_update(DoublyLinkedList *dll, int old_val, int new_val)
{
    size_t old_size = dll->size;
    dll_delete(dll, old_val);

    /* ensure we are updating instead of inserting */
    if (old_size > dll->size)
        dll_insert(dll, new_val);
}

void dll_reverse(DoublyLinkedList *dll)
{
    /*
     * NOTE !!!
     *
     * Variables cur, prev, and next are used to point to nodes
     * in the original "next" order of the list.
     *
     * 1. Before the loop, we update the tail node's 'prev' pointer.
     * 2. Inside the loop, we reverse the 'next' and 'prev' links of the current node.
     * 3. After the loop, we update the head node's 'next' pointer.
     *
     * During the loop:
     * - The first node's 'next' is updated to point to the tail.
     * - The last node's 'prev' has not yet been updated to point to the head
     *   (still the tail), so we need to handle that after the loop.
     */

    /* reverse the link */
    Node *cur = dll->dummy_head.next, *prev = &dll->dummy_tail, *next;
    prev->prev = cur;   /* update the tail node */
    while (cur != &dll->dummy_tail) {
        next = cur->next;
        cur->next = prev;
        cur->prev = next;
        prev = cur;
        cur = next;
    }
    /* update the head node */
    dll->dummy_head.next = prev;
    prev->prev = &dll->dummy_head;
}
