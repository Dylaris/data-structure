#include <criterion/criterion.h>
#include "queue_array.h"

Test(queue_array, test_queue_new)
{
    Queue *queue = queue_new(1);

    cr_assert(queue != NULL);
    cr_assert_eq(queue->front, -1);
    cr_assert_eq(queue->rear, -1);
    cr_assert_eq(queue->size, 1);
    cr_assert(queue->ptr != NULL);

    queue_destroy(queue);
}

Test(queue_array, test_queue_push_and_pop)
{
    Queue *queue = queue_new(4);

    queue_push(queue, 1);
    queue_push(queue, 2);
    queue_push(queue, 3);
    queue_push(queue, 4);
    cr_assert_eq(queue->front, 0);
    cr_assert_eq(queue->rear, 3);
    cr_assert_eq(queue->ptr[queue->front], 1);
    cr_assert_eq(queue->ptr[queue->rear], 4);

    cr_assert_eq(queue_pop(queue), 1);
    cr_assert_eq(queue->front, 1);
    queue_push(queue, 5);
    cr_assert_eq(queue->rear, 0);
    cr_assert_eq(queue->ptr[queue->front], 2);
    cr_assert_eq(queue->ptr[queue->rear], 5);

    cr_assert_eq(queue_pop(queue), 2);
    cr_assert_eq(queue->front, 2);
    queue_push(queue, 6);
    cr_assert_eq(queue->rear, 1);
    cr_assert_eq(queue->ptr[queue->front], 3);
    cr_assert_eq(queue->ptr[queue->rear], 6);

    queue_destroy(queue);
}

Test(queue_array, test_queue_front)
{
    Queue *queue = queue_new(4);

    queue_push(queue, 1);
    queue_push(queue, 2);
    queue_push(queue, 3);
    queue_push(queue, 4);

    cr_assert_eq(queue_front(queue), queue->ptr[queue->front]);

    queue_destroy(queue);
}

Test(queue_array, test_queue_rear)
{
    Queue *queue = queue_new(4);

    queue_push(queue, 1);
    queue_push(queue, 2);
    queue_push(queue, 3);
    queue_push(queue, 4);

    cr_assert_eq(queue_rear(queue), queue->ptr[queue->rear]);

    queue_destroy(queue);
}
