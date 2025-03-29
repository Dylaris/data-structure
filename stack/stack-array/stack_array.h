#ifndef STACK_ARRAY_H
#define STACK_ARRAY_H

#include <stdlib.h>
#include <stdio.h>

#define ERR(msg) do { \
        fprintf(stderr, "error: %s at <%s:%d>\n", \
            msg, __FILE__, __LINE__); \
        exit(1); \
    } while (0)
#define STACK_EMPTY -1
#define INVALID_VAL -2147483648     /* INT_MIN */
#define MIN_STACK_SIZE 2            /* Used to limit the stack shrink (2 is used to test) */
#define PREFIX  1
#define INFIX   2
#define POSTFIX 3

typedef struct Stack {
    int top;
    int *slots;
    size_t size;
} Stack;

Stack *stack_new(size_t size);
void stack_destroy(Stack *stack);
void stack_push(Stack *stack, int value);
int stack_pop(Stack *stack);
int stack_top(Stack *stack);
void stack_print(Stack *stack);
char *stack_reverse(char *str, int is_literal);
char *stack_convert_expr(char *expr, size_t size, int src, int dest);
#define stack_is_empty(stack) (stack->top == STACK_EMPTY)
#define stack_is_full(stack) (stack->top == (stack->size - 1))

#endif /* STACK_ARRAY_H */
