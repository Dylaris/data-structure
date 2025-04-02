#include <criterion/criterion.h>
#include "bst.h"

Test(bst, test_bst_insert)
{
    Node *root = NULL;

    root = bst_insert(root, 5);
    root = bst_insert(root, 1);
    root = bst_insert(root, 4);
    root = bst_insert(root, 2);
    root = bst_insert(root, 6);
    root = bst_insert(root, 9);
    root = bst_insert(root, 8);

    cr_assert_eq(root->data, 5);
    cr_assert_eq(root->left->data, 1);
    cr_assert_eq(root->right->data, 6);

    bst_traverse(root, IN_ORDER);
    bst_traverse(root, PRE_ORDER);
    bst_traverse(root, POST_ORDER);

    bst_destroy(root);
}

Test(bst, test_bst_search)
{
    Node *root = NULL;

    root = bst_insert(root, 5);
    root = bst_insert(root, 1);
    root = bst_insert(root, 4);
    root = bst_insert(root, 2);
    root = bst_insert(root, 6);
    root = bst_insert(root, 9);
    root = bst_insert(root, 8);

    cr_assert_eq(bst_search(root, 5)->data, 5);
    cr_assert_eq(bst_search(root, 2)->data, 2);
    cr_assert_eq(bst_search(root, 8)->data, 8);
    cr_assert_eq(bst_search(root, 10), NULL);
    cr_assert_eq(bst_search(root, 0), NULL);

    bst_destroy(root);
}

Test(bst, test_bst_find_max_min_height)
{
    Node *root = NULL;

    root = bst_insert(root, 5);
    root = bst_insert(root, 1);
    root = bst_insert(root, 4);
    root = bst_insert(root, 2);
    root = bst_insert(root, 6);
    root = bst_insert(root, 9);
    root = bst_insert(root, 8);

    cr_assert_eq(bst_find_max(root)->data, 9);
    cr_assert_eq(bst_find_min(root)->data, 1);
    cr_assert_eq(bst_find_height(root), 3);

    bst_destroy(root);
}

Test(bst, test_bst_verify)
{
    Node *root = NULL;

    root = bst_insert(root, 5);
    root = bst_insert(root, 1);
    root = bst_insert(root, 4);
    root = bst_insert(root, 2);
    root = bst_insert(root, 6);
    root = bst_insert(root, 9);
    root = bst_insert(root, 8);
    cr_assert(bst_verify(root) == TRUE);
    bst_destroy(root);

    /* Build a wrong bst */
    Node w_left_left = (Node) {
        .data = 7,
        .left = NULL,
        .right = NULL
    };
    Node w_left = (Node) {
        .data = 4,
        .left = NULL,
        .right = &w_left_left
    };
    Node w_right = (Node) {
        .data = 8,
        .left = NULL,
        .right = NULL
    };
    Node w_root = (Node) {
        .data = 5,
        .left = &w_left,
        .right = &w_right
    };
    cr_assert(bst_verify(&w_root) == FALSE);
}

Test(bst, test_bst_remove)
{
    Node *root = NULL;

    root = bst_insert(root, 5);
    root = bst_insert(root, 1);
    root = bst_insert(root, 4);
    root = bst_insert(root, 2);
    root = bst_insert(root, 6);
    root = bst_insert(root, 9);
    root = bst_insert(root, 8);
    bst_traverse(root, IN_ORDER);

    root = bst_remove(root, 10); cr_assert(bst_verify(root) == TRUE);
    root = bst_remove(root,  8); cr_assert(bst_verify(root) == TRUE);
    root = bst_remove(root,  1); cr_assert(bst_verify(root) == TRUE);
    root = bst_remove(root,  5); cr_assert(bst_verify(root) == TRUE);
    bst_traverse(root, IN_ORDER);

    root = bst_insert(root, 8); cr_assert(bst_verify(root) == TRUE);
    root = bst_insert(root, 1); cr_assert(bst_verify(root) == TRUE);
    root = bst_insert(root, 5); cr_assert(bst_verify(root) == TRUE);
    bst_traverse(root, IN_ORDER);

    bst_destroy(root);
}
