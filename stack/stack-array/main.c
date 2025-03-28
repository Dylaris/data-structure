#include "stack_array.h"

int main(void)
{
    Stack *stack = stack_new(1);

    stack_push(stack, 1);
    stack_push(stack, 2);
    stack_push(stack, 3);
    stack_push(stack, 4);
    stack_push(stack, 5);
    stack_push(stack, 6);
    stack_push(stack, 7);
    stack_push(stack, 8);

    stack_print(stack);

    int value;
    value = stack_pop(stack); printf("pop value: %d\n", value);
    value = stack_pop(stack); printf("pop value: %d\n", value);
    value = stack_pop(stack); printf("pop value: %d\n", value);
    value = stack_pop(stack); printf("pop value: %d\n", value);

    stack_print(stack);

    stack_destroy(stack);
}
