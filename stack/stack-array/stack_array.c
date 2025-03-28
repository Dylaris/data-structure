#include "stack_array.h"

Stack *stack_new(size_t size)
{
    Stack *stack = malloc(sizeof(Stack));
    if (!stack) ERR("new stack");

    stack->size = (size >= MIN_STACK_SIZE) ? size : MIN_STACK_SIZE;
    stack->slots = malloc(sizeof(int) * (stack->size));
    if (!(stack->slots)) ERR("new slots of stack");

    for (int i = 0; i < size; i++)
        stack->slots[i] = INVALID_VAL;
    stack->top = STACK_EMPTY;

    return stack;
}

void stack_destroy(Stack *stack)
{
    free(stack->slots);
    free(stack);
}

void stack_push(Stack *stack, int value)
{
    if (stack_is_full(stack)) {
        int *new_slots = realloc(stack->slots, 2 * stack->size * sizeof(int));
        if (!new_slots) ERR("failed to resize");
        stack->slots = new_slots;
        stack->size *= 2;
    }
    stack->slots[++stack->top] = value;
}

int stack_pop(Stack *stack)
{
    if (stack_is_empty(stack))
        return INVALID_VAL;
    int value = stack->slots[stack->top--];

    if (stack->top < stack->size / 2 && stack->size >= MIN_STACK_SIZE) {
        int *new_slots = realloc(stack->slots, stack->size / 2 * sizeof(int));
        if (!new_slots) ERR("failed to resize");
        stack->slots = new_slots;
        stack->size /= 2;
    }

    return value;
}

void stack_print(Stack *stack)
{
    for (int i = 0; i <= stack->top; i++)
        printf(" %d", stack->slots[i]);
    printf("\n");
}
