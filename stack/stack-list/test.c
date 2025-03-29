#include <criterion/criterion.h>
#include "stack_list.h"

Test(stack_array, test_stack_new)
{
    Stack *stack = stack_new();

    cr_assert(stack != NULL, "stack != NULL");
    cr_assert(stack->top == NULL, "stack->top == NULL");
    cr_assert_eq(stack->size, 0, "stack->size == 0");
    cr_assert(stack_is_empty(stack) == 1, "stack is empty");

    stack_destroy(stack);
}

Test(stack_array, test_stack_push)
{
    Stack *stack = stack_new();
    size_t count = 0;

    stack_push(stack, 1); count++;
    stack_push(stack, 2); count++;
    stack_push(stack, 3); count++;
    cr_assert_eq(stack->top->data, 3);
    cr_assert_eq(stack->size, count);
    cr_assert(stack_is_empty(stack) == 0);

    stack_push(stack, 4); count++;
    cr_assert_eq(stack->top->data, 4);
    cr_assert_eq(stack->size, count);
    cr_assert(stack_is_empty(stack) == 0);

    stack_destroy(stack);
}

Test(stack_array, test_stack_pop)
{
    Stack *stack = stack_new();
    size_t count = 0;

    stack_push(stack, 1); count++;
    stack_push(stack, 2); count++;
    stack_push(stack, 3); count++;
    stack_push(stack, 4); count++;
    cr_assert_eq(stack->size, count);

    cr_assert_eq(stack_pop(stack), 4); count--;
    cr_assert_eq(stack->size, count);
    cr_assert_eq(stack->top->data, 3);

    cr_assert_eq(stack_pop(stack), 3); count--;
    cr_assert_eq(stack->size, count);
    cr_assert_eq(stack->top->data, 2);

    cr_assert_eq(stack_pop(stack), 2); count--;
    cr_assert_eq(stack->size, count);
    cr_assert_eq(stack->top->data, 1);
    cr_assert(stack_is_empty(stack) == 0);

    stack_destroy(stack);
}

Test(stack_array, test_stack_top)
{
    Stack *stack = stack_new(3);

    stack_push(stack, 1);
    stack_push(stack, 2);
    cr_assert_eq(stack_top(stack), 2);
    stack_pop(stack);
    cr_assert_eq(stack_top(stack), 1);
    stack_pop(stack);
    cr_assert_eq(stack_top(stack), INVLAID_VAL);

    stack_destroy(stack);
}
