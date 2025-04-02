#ifndef BST_H
#define BST_H

#include <stdio.h>
#include <stdlib.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define ERR(msg) do { \
        fprintf(stderr, "%s\n", msg); \
        exit(0); \
    } while (0)
#define INVALID     -2147483648
#define PRE_ORDER   0
#define IN_ORDER    1
#define POST_ORDER  2
#define LEVEL_ORDER 3
#define TRUE        1
#define FALSE       0

typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} Node;

void bst_destroy(Node *root);
Node *bst_insert(Node *root, int data);
Node *bst_remove(Node *root, int data);
void bst_traverse(Node *root, int mode);
Node *bst_search(Node *root, int data);
Node *bst_find_max(Node *root);
Node *bst_find_min(Node *root);
int bst_find_height(Node *root);
int bst_verify(Node *root);     /* Verify the tree is a binary search tree */
Node *bst_get_successor(Node *root, int data);

#endif /* BST_H */
