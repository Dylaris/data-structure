#include "stack_array.h"
#include <string.h>
#include <ctype.h>

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

int stack_top(Stack *stack)
{
    if (!stack_is_empty(stack))
        return stack->slots[stack->top];
    return INVALID_VAL;
}

enum OP {
    ADD,    /* + */   
    SUB,    /* - */
    MUL,    /* * */ 
    DIV,    /* / */
    INVAILD
};

static int op_priority[] = { 1, 1, 2, 2 };    /* corresponding to enum OP */

static int char2op(char c)
{
    switch (c) {
    case '+': return ADD;
    case '-': return SUB;
    case '*': return MUL;
    case '/': return DIV;
    default:  return INVAILD;
    }
}

#define is_left_paren(c)    (c == '(')
#define is_right_paren(c)   (c == ')')
#define is_operator(c)      (c == '+' || c == '-' || c == '*' || c == '/')
#define is_operand(c)       (isalnum(c))
#define high_priority(a, b) (op_priority[char2op(a)] > op_priority[char2op(b)])

static char *stack_expr_in2post(char *expr, size_t len)
{
    Stack *stack = stack_new(100);
    char *res = malloc(len + 1);
    if (!res) ERR("malloc in stack_expr_in2post");

    char c;
    int off = 0;
    for (int i = 0; i < len; i++) {
        c = expr[i];
        if (is_operand(c)) {
            res[off++] = c;
        } else if (is_operator(c)) {
            while (!stack_is_empty(stack) && !is_left_paren(stack_top(stack))
                    && high_priority(stack_top(stack), c))
                res[off++] = stack_pop(stack);
            stack_push(stack, c);
        } else if (is_left_paren(c)) {
            stack_push(stack, c);
        } else if (is_right_paren(c)) {
            while (!stack_is_empty(stack) && !is_left_paren(stack_top(stack)))
                res[off++] = stack_pop(stack);
            stack_pop(stack);   /* pop the '(' */
        }
    } 
    while (!stack_is_empty(stack))
        res[off++] = stack_pop(stack);
    res[off] = '\0';

    stack_destroy(stack);

    return res;
}

static char *stack_expr_in2pre(char *expr, size_t len)
{
    /*
     * 'Infix to Prefix' is the opposite of 'Infix to Postfix'. In this case,
     * the expression is scanned from right to left. Additionally, the opening
     * parenthesis is ')' instead of '('—this must be taken into account.
     *
     * Other steps remain the same as the 'Infix to Postfix' conversion. The key 
     * difference is that after processing the expression, we need to reverse 
     * the result, as Prefix notation differs from Postfix in terms of operand 
     * and operator order.
     */

    Stack *stack = stack_new(100);
    char *res = malloc(len + 1);
    if (!res) ERR("malloc in stack_expr_in2pre");

    char c;
    int off = 0;

    for (int i = len - 1; i >= 0; i--) {
        c = expr[i];
        if (is_operand(c)) {
            res[off++] = c;
        } else if (is_operator(c)) {
            while (!stack_is_empty(stack) && !is_right_paren(stack_top(stack))
                    && high_priority(stack_top(stack), c))
                res[off++] = stack_pop(stack);
            stack_push(stack, c);
        } else if (is_right_paren(c)) {
            stack_push(stack, c);
        } else if (is_left_paren(c)) {
            while (!stack_is_empty(stack) && !is_right_paren(stack_top(stack)))
                res[off++] = stack_pop(stack);
            stack_pop(stack);   /* pop the ')' */
        }
    } 
    while (!stack_is_empty(stack))
        res[off++] = stack_pop(stack);
    res[off] = '\0';
    res = stack_reverse(res, 0);    /* reverse the order between operator and operand */

    stack_destroy(stack);

    return res;
}

/*
 * Use a stack to build an expression tree. Once the tree is built,
 * we can perform pre-order, post-order, or in-order traversal to
 * 
 * So, no need to bother implementing the functions below — we've got it all
 * covered with tree magic! :-))
 */
static char *stack_expr_pre2in(char *expr, size_t len) { }
static char *stack_expr_pre2post(char *expr, size_t len) { }
static char *stack_expr_post2pre(char *expr, size_t len) { }
static char *stack_expr_post2in(char *expr, size_t len) { }

typedef struct ConversionRule {
    int src;
    int dest;
    char* (*convert_func)(char* expr, size_t len);
} ConversionRule;

ConversionRule conversion_rules[] = {
    { INFIX  , POSTFIX, stack_expr_in2post  },
    { INFIX  , PREFIX , stack_expr_in2pre   },
    { PREFIX , INFIX  , stack_expr_pre2in   },
    { PREFIX , POSTFIX, stack_expr_pre2post },
    { POSTFIX, PREFIX , stack_expr_post2pre },
    { POSTFIX, INFIX  , stack_expr_post2in  }
};

char *stack_convert_expr(char *expr, size_t len, int src, int dest)
{
    if (src == dest || len < 3) return expr;

    for (int i = 0; i < sizeof(conversion_rules) / sizeof(ConversionRule); i++) {
        if (conversion_rules[i].src == src && conversion_rules[i].dest == dest) {
            return conversion_rules[i].convert_func(expr, len);
        }
    }

    /* do not find a rule */
    return expr;
}
