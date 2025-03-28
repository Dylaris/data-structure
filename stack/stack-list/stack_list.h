#ifndef STACK_LIST_H
#define STACK_LIST_H

#include <stdlib.h>
#include <stdio.h>

#define ERR(msg) do { \
        fprintf(stderr, "error: %s at <%s:%d>\n", \
            msg, __FILE__, __LINE__); \
        exit(1); \
    } while (0)
#define INVLAID_VAL -2147483648

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct Stack {
    Node *top;
    size_t size;
} Stack;

Stack *stack_new();
void stack_destroy(Stack *stack);
void stack_push(Stack *stack, int value);
int stack_pop(Stack *stack);
void stack_print(Stack *stack);
#define stack_is_empty(stack) (stack->top == NULL)

#endif /* STACK_ARRAY_H */
