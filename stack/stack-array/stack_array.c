#include "stack_array.h"
#include <string.h>

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

char *stack_reverse(char *str, int is_literal)
{
    char *res = NULL;
    Stack *stack = stack_new(100);

    if (is_literal) {
        size_t len = strlen(str);
        res = malloc(sizeof(char) * len);
        if (!res) ERR("new string in stack_reverse");

        for (int i = 0; i < len; i++)
            stack_push(stack, str[i]);
        for (int i = 0; i < len; i++)
            res[i] = stack_pop(stack);
        res[len] = '\0';
    } else {
        size_t len = 0;
        while (str[len++] != '\0');
        len--;
        res = str;

        for (int i = 0; i < len; i++)
            stack_push(stack, str[i]);
        for (int i = 0; i < len; i++)
            res[i] = stack_pop(stack);
        res[len] = '\0';
    }

    stack_destroy(stack);

    return res;
}

enum OP {
    ADD,    /* + */   
    SUB,    /* - */
    MUL,    /* * */ 
    DIV,    /* / */
    LP,     /* ( */
    RP      /* ) */
};

static int op_priority[] = { 1, 1, 2, 2, 4, 4 };    /* corresponding to enum OP */

static char *stack_expr_in2post(char *expr, size_t size)
{

}

static char *stack_expr_in2pre(char *expr, size_t size)
{

}

static char *stack_expr_pre2in(char *expr, size_t size)
{

}

static char *stack_expr_pre2post(char *expr, size_t size)
{

}

static char *stack_expr_post2pre(char *expr, size_t size)
{

}

static char *stack_expr_post2in(char *expr, size_t size)
{

}

typedef struct ConversionRule {
    int src;
    int dest;
    char* (*convert_func)(char* expr, size_t size);
} ConversionRule;

ConversionRule conversion_rules[] = {
    { INFIX  , POSTFIX, stack_expr_in2post  },
    { INFIX  , PREFIX , stack_expr_in2pre   },
    { PREFIX , INFIX  , stack_expr_pre2in   },
    { PREFIX , POSTFIX, stack_expr_pre2post },
    { POSTFIX, PREFIX , stack_expr_post2pre },
    { POSTFIX, INFIX  , stack_expr_post2in  }
};

char *stack_convert_expr(char *expr, size_t size, int src, int dest)
{
    if (src == dest || size < 3) return expr;

    for (int i = 0; i < sizeof(conversion_rules) / sizeof(ConversionRule); i++) {
        if (conversion_rules[i].src == src && conversion_rules[i].dest == dest) {
            return conversion_rules[i].convert_func(expr, size);
        }
    }

    /* do not find a rule */
    return expr;
}
