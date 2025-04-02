#include "bst.h"

int main(void)
{
    Node *root = NULL;

    root = bst_insert(root, 5);
    root = bst_insert(root, 2);
    root = bst_insert(root, 4);
    root = bst_insert(root, 8);
    root = bst_insert(root, 1);
    root = bst_insert(root, 9);
    root = bst_insert(root, 7);

    bst_traverse(root, IN_ORDER);
    printf("Height: %d\n", bst_find_height(root));
    printf("Max value: %d\n", bst_find_max(root)->data);
    printf("Min value: %d\n", bst_find_min(root)->data);

    root = bst_remove(root, 2);
    root = bst_remove(root, 4);
    root = bst_remove(root, 8);
    root = bst_remove(root, 1);

    bst_traverse(root, IN_ORDER);
    printf("Height: %d\n", bst_find_height(root));
    printf("Max value: %d\n", bst_find_max(root)->data);
    printf("Min value: %d\n", bst_find_min(root)->data);

    bst_destroy(root);

    return 0;
}
