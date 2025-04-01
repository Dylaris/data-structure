#include <criterion/criterion.h>
#include "bst.h"

Test(bst, test_bst_insert)
{
    Node *root = NULL;

    bst_insert(&root, 5);
    bst_insert(&root, 1);
    bst_insert(&root, 4);
    bst_insert(&root, 2);
    bst_insert(&root, 6);
    bst_insert(&root, 9);
    bst_insert(&root, 8);

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

    bst_insert(&root, 5);
    bst_insert(&root, 1);
    bst_insert(&root, 4);
    bst_insert(&root, 2);
    bst_insert(&root, 6);
    bst_insert(&root, 9);
    bst_insert(&root, 8);

    cr_assert_eq(bst_search(root, 5), TRUE);
    cr_assert_eq(bst_search(root, 2), TRUE);
    cr_assert_eq(bst_search(root, 8), TRUE);
    cr_assert_eq(bst_search(root, 10), FALSE);
    cr_assert_eq(bst_search(root, 0), FALSE);

    bst_destroy(root);
}

Test(bst, test_bst_find_max_min_height)
{
    Node *root = NULL;

    bst_insert(&root, 5);
    bst_insert(&root, 1);
    bst_insert(&root, 4);
    bst_insert(&root, 2);
    bst_insert(&root, 6);
    bst_insert(&root, 9);
    bst_insert(&root, 8);

    cr_assert_eq(bst_find_max(root), 9);
    cr_assert_eq(bst_find_min(root), 1);
    cr_assert_eq(bst_find_height(root), 3);

    bst_destroy(root);
}
