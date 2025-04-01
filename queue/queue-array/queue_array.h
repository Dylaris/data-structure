#ifndef QUEUE_ARRAY_H
#define QUEUE_ARRAY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERR(msg) do { \
        fprintf(stderr, "%s\n", msg); \
        exit(1); \
    } while (0)
#define INVALID -2147483648
#define queue_is_full(q) (q->front == (q->rear + 1) % q->size)
#define queue_is_empty(q) (q->front == -1 && q->rear == -1)

typedef struct Queue {
    int front;      /* index of front element */
    int rear;       /* index of rear element */
    size_t size;    /* size of queue */
    int *ptr;       /* point to the start address of queue */
} Queue;

Queue *queue_new(size_t size);
void queue_destroy(Queue *queue);
void queue_push(Queue *queue, int val);
int queue_pop(Queue *queue);
int queue_front(Queue *queue);
int queue_rear(Queue *queue);
void queue_print(Queue *queue);

#endif /* QUEUE_ARRAY_H */
