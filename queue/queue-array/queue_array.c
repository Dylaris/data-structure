#include "queue_array.h"

Queue *queue_new(size_t size)
{
    Queue *queue = malloc(sizeof(Queue));
    if (!queue) ERR("new queue");

    queue->ptr = malloc(sizeof(int) * size);
    if (!queue->ptr) ERR("new memory space for queue");
    queue->size = size;
    queue->front = -1;
    queue->rear = -1;

    return queue;
}

void queue_destroy(Queue *queue)
{
    free(queue->ptr);
    free(queue);
}

void queue_push(Queue *queue, int val)
{
    if (queue_is_full(queue)) {
        ERR("queue is full");
    } else if (queue_is_empty(queue)) {
        queue->front = 0;
        queue->rear = 0;
    } else {
        queue->rear = (queue->rear + 1) % queue->size;
    }
    queue->ptr[queue->rear] = val;
}

int queue_pop(Queue *queue)
{
    int front = queue->front;

    if (queue_is_empty(queue)) {
        return INVALID;
    } else if (queue->front == 0 && queue->rear == 0) {
        queue->front = -1;
        queue->rear = -1;
    } else {
        queue->front = (queue->front + 1) % queue->size;
    }
    return queue->ptr[front];
}

int queue_front(Queue *queue)
{
    if (queue_is_empty(queue)) return INVALID;
    return queue->ptr[queue->front];
}

int queue_rear(Queue *queue)
{
    if (queue_is_empty(queue)) return INVALID;
    return queue->ptr[queue->rear];
}

void queue_print(Queue *queue)
{
    if (queue_is_empty(queue)) {
        puts("queue is empty");
        return;
    }

    int idx = queue->front;
    do {
        printf("%d -> ", queue->ptr[idx]);
        idx = (idx + 1) % queue->size;
    } while (idx != queue->front);
    printf("\n");
}
