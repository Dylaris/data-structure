#include "queue_list.h"

Queue *queue_new()
{
    Queue *queue = malloc(sizeof(Queue));
    if (!queue) ERR("new queue");

    queue->front = NULL;
    queue->rear = NULL;
    queue->dummy_head = (Node) {
        .data = INVALID,
        .next = queue->front
    };

    return queue;
}

void queue_destroy(Queue *queue)
{
    Node *cur = queue->dummy_head.next, *next = NULL;
    while (cur) {
        next = cur->next;
        free(cur);
        cur = next;
    }
    free(queue);
}

void queue_push(Queue *queue, int val)
{
    Node *node = malloc(sizeof(Node));
    if (!node) ERR("new node");
    node->data = val;
    node->next = NULL;

    if (queue_is_empty(queue)) {
        queue->front = node;
        queue->rear = node;
        queue->dummy_head.next = queue->front;
    } else {
        queue->rear->next = node;
        queue->rear = node;
    }
}

int queue_pop(Queue *queue)
{
    int val = INVALID;

    if (queue_is_empty(queue)) {
        return val;
    } else if (queue->front == queue->rear) {
        /* just one element */
        val = queue->front->data;
        free(queue->front);
        queue->front = NULL;
        queue->rear = NULL;
        queue->dummy_head.next = NULL;
    } else {
        val = queue->front->data;
        queue->dummy_head.next = queue->front->next;
        free(queue->front);
        queue->front = queue->dummy_head.next;
    }
    return val;
}

int queue_front(Queue *queue)
{
    if (queue_is_empty(queue)) return INVALID;
    return queue->front->data;
}

int queue_rear(Queue *queue)
{
    if (queue_is_empty(queue)) return INVALID;
    return queue->rear->data;
}

void queue_print(Queue *queue)
{
    if (queue_is_empty(queue)) {
        puts("queue is empty");
        return;
    }

    Node *cur = queue->front;
    while (cur) {
        printf("%d -> ", cur->data);
        cur = cur->next;
    }
    printf("\n");
}
