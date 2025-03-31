#include <criterion/criterion.h>
#include "queue_list.h"

Test(queue_array, test_queue_new)
{
    Queue *queue = queue_new();

    cr_assert(queue != NULL);
    cr_assert(queue->dummy_head.next == NULL);
    cr_assert_eq(queue->dummy_head.data, INVALID);
    cr_assert(queue->front == NULL);
    cr_assert(queue->rear == NULL);

    queue_destroy(queue);
}

Test(queue_array, test_queue_push_and_pop)
{
    Queue *queue = queue_new(4);

    queue_push(queue, 1);
    queue_push(queue, 2);
    queue_push(queue, 3);
    queue_push(queue, 4);
    cr_assert_eq(queue->dummy_head.next, queue->front);
    cr_assert_eq(queue->front->data, 1);
    cr_assert_eq(queue->rear->data, 4);

    cr_assert_eq(queue_pop(queue), 1);
    cr_assert_eq(queue->dummy_head.next, queue->front);
    cr_assert_eq(queue->front->data, 2);

    queue_push(queue, 5);
    cr_assert_eq(queue->rear->data, 5);

    queue_destroy(queue);
}

Test(queue_array, test_queue_front)
{
    Queue *queue = queue_new(4);

    queue_push(queue, 1);
    queue_push(queue, 2);
    queue_push(queue, 3);
    queue_push(queue, 4);

    cr_assert_eq(queue_front(queue), queue->front->data);

    queue_destroy(queue);
}

Test(queue_array, test_queue_rear)
{
    Queue *queue = queue_new(1);

    queue_push(queue, 1);

    cr_assert_eq(queue_rear(queue), queue->rear->data);
    cr_assert_eq(queue->rear, queue->front);

    queue_destroy(queue);
}
