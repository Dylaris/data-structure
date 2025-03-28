#include "stack_list.h"

Stack *stack_new()
{
    Stack *stack = malloc(sizeof(Stack));
    if (!stack) ERR("new stack");

    stack->size = 0;
    stack->top = NULL;

    return stack;
}

void stack_destroy(Stack *stack)
{
    Node *cur = stack->top, *next;
    while (cur) {
        next = cur->next;
        free(cur);
        cur = next;
    }
    free(stack);
}

void stack_push(Stack *stack, int value)
{
    Node *node = malloc(sizeof(Node));
    if (!node) ERR("new node");

    node->data = value;
    node->next = stack->top;

    stack->top = node;
    stack->size++;
}

int stack_pop(Stack *stack)
{
    if (stack_is_empty(stack))
        return INVLAID_VAL;
    int value = stack->top->data;
    Node *tmp = stack->top;
    stack->top = stack->top->next;
    stack->size--;
    free(tmp);
    return value;
}

void stack_print(Stack *stack)
{
    Node *cur = stack->top, *next;
    while (cur) {
        next = cur->next;
        printf(" %d", cur->data);
        cur = next;
    }
    printf("\n");
}
