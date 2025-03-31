#include "queue_list.h"

int main(void)
{
    Queue *queue = queue_new();

    queue_push(queue, 1);
    queue_push(queue, 2);
    queue_push(queue, 3);
    queue_push(queue, 4);

    printf("Front of queue is: %d\n", queue_front(queue));
    printf("Rear of queue is: %d\n", queue_rear(queue));
    queue_print(queue);

    queue_pop(queue);
    queue_pop(queue);
    queue_pop(queue);
    queue_push(queue, 5);
    queue_push(queue, 7);
    queue_push(queue, 9);
    printf("Front of queue is: %d\n", queue_front(queue));
    printf("Rear of queue is: %d\n", queue_rear(queue));
    queue_print(queue);

    queue_destroy(queue);

    return 0;
}
