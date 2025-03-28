#include <criterion/criterion.h>
#include "stack_array.h"

Test(stack_array, test_stack_new)
{
    Stack *stack = stack_new(10);

    cr_assert(stack != NULL);
    cr_assert_eq(stack->top, STACK_EMPTY);
    cr_assert(stack->slots != NULL);
    cr_assert_eq(stack->size, 10);
    cr_assert(stack_is_empty(stack) == 1);
    cr_assert(stack_is_full(stack) == 0);

    stack_destroy(stack);
}

Test(stack_array, test_stack_push)
{
    Stack *stack = stack_new(3);
    size_t count = 0;

    stack_push(stack, 1); count++;
    stack_push(stack, 2); count++;
    stack_push(stack, 3); count++;
    cr_assert_eq(stack->top, count - 1);
    cr_assert(stack_is_empty(stack) == 0);
    cr_assert(stack_is_full(stack) == 1);

    stack_push(stack, 4); count++;
    cr_assert_eq(stack->top, count - 1);
    cr_assert_eq(stack->size, 6);
    cr_assert(stack_is_empty(stack) == 0);
    cr_assert(stack_is_full(stack) == 0);

    stack_destroy(stack);
}

Test(stack_array, test_stack_pop)
{
    Stack *stack = stack_new(3);
    size_t count = 0;

    stack_push(stack, 1); count++;
    stack_push(stack, 2); count++;
    stack_push(stack, 3); count++;
    stack_push(stack, 4); count++;
    cr_assert_eq(stack->size, 6);

    cr_assert_eq(stack_pop(stack), 4); count--;
    cr_assert_eq(stack->size, 3);
    cr_assert_eq(stack_pop(stack), 3); count--;
    cr_assert_eq(stack_pop(stack), 2); count--;
    cr_assert_eq(stack->size, 1);
    cr_assert_eq(stack->top, count - 1);

    stack_destroy(stack);
}
