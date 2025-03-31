#ifndef QUEUE_LIST_H
#define QUEUE_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERR(msg) do { \
        fprintf(stderr, "%s\n", msg); \
        exit(1); \
    } while (0)
#define INVALID -2147483647
#define queue_is_empty(q) (q->dummy_head.next == NULL)

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct Queue {
    Node dummy_head;
    Node *front;    /* point to front element */
    Node *rear;     /* point to rear element */
} Queue;

Queue *queue_new();
void queue_destroy(Queue *queue);
void queue_push(Queue *queue, int val);
int queue_pop(Queue *queue);
int queue_front(Queue *queue);
int queue_rear(Queue *queue);
void queue_print(Queue *queue);

#endif /* QUEUE_LIST_H */
