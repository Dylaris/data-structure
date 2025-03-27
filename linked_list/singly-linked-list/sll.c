#include "sll.h"
#include <stdio.h>
#include <stdlib.h>

SinglyLinkedList *sll_new()
{
    SinglyLinkedList *sll = malloc(sizeof(SinglyLinkedList));
    if (!sll) ERR("new singly linked list");

    sll->dummy_head= (Node) {INVALID_DATA, NULL};
    sll->size = 0;

    return sll;
}

void sll_destroy(SinglyLinkedList *sll)
{
    Node *cur = sll->dummy_head.next, *next = NULL;
    while (cur != NULL) {
        next = cur->next;
        free(cur);
        cur = next;
    }
    free(sll);
}

void sll_print(SinglyLinkedList *sll)
{
    Node *cur = sll->dummy_head.next;
    while (cur != NULL) {
        printf(" %d", cur->data);
        cur = cur->next;
    }
    printf("\n");
}

void sll_insert(SinglyLinkedList *sll, int value)
{
    /* new a insert node */
    Node *node = malloc(sizeof(Node));
    if (!node) ERR("new a node");
    node->data = value;
    node->next = NULL;

    /* find the insert position */
    Node *cur = sll->dummy_head.next, *prev = &sll->dummy_head;
    while (cur != NULL) {
        if (cur->data > value) break;
        prev = cur;
        cur = cur->next;
    }

    /* insert (update the link)  */
    node->next = cur;
    prev->next = node;

    /* update the sll */
    (sll->size)++;
}

void sll_delete(SinglyLinkedList *sll, int value)
{
    /* find the delete position */
    Node *cur = sll->dummy_head.next, *prev = &sll->dummy_head;
    while (cur != NULL) {
        if (cur->data == value) break;
        prev = cur;
        cur = cur->next;
    }

    /* find it */
    if (cur != NULL) {
        /* delete (update the link) */
        prev->next = cur->next;
        free(cur);

        /* update the sll */
        (sll->size)--;
    }
}

Node *sll_search(SinglyLinkedList *sll, int value)
{
    /* find the position */
    Node *cur = sll->dummy_head.next;
    while (cur != NULL) {
        if (cur->data == value) break;
        cur = cur->next;
    }

    /* NULL -> not found */
    return cur;
}

void sll_update(SinglyLinkedList *sll, int old_val, int new_val)
{
    size_t old_size = sll->size;
    sll_delete(sll, old_val);

    /* ensure we are updating instead of inserting */
    if (old_size > sll->size)
        sll_insert(sll, new_val);
}

void sll_reverse(SinglyLinkedList *sll)
{
    /* reverse the link */
    Node *cur = sll->dummy_head.next, *prev = NULL, *next;
    while (cur != NULL) {
        next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }
    sll->dummy_head.next = prev;
}
