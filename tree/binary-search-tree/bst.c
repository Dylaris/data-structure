#include "bst.h"

void bst_destroy(Node *root)
{
    if (!root) return;

    bst_destroy(root->left);
    bst_destroy(root->right);
    free(root);
}

static Node *new_node(int data)
{
    Node *node = malloc(sizeof(Node));
    if (!node) ERR("new node");

    node->data = data;
    node->left = NULL;
    node->right = NULL;

    return node;
}

void bst_insert(Node **root, int data)
{
    if (!(*root))
        *root = new_node(data);
    else if (data <= (*root)->data)
        bst_insert(&(*root)->left, data);
    else
        bst_insert(&(*root)->right, data);
}

static void pre_traverse(Node *root)
{
    if (!root) return;
    printf("%d -> ", root->data);
    pre_traverse(root->left);
    pre_traverse(root->right);
}

static void in_traverse(Node *root)
{
    if (!root) return;
    in_traverse(root->left);
    printf("%d -> ", root->data);
    in_traverse(root->right);
}

static void post_traverse(Node *root)
{
    if (!root) return;
    post_traverse(root->left);
    post_traverse(root->right);
    printf("%d -> ", root->data);
}

static void level_traverse(Node *root)
{
    /*
     * Use a queue to implement level-order traversal (BFS) for the tree.
     * 
     * I have implemented a queue, but it only supports elements of type `int`.
     * Therefore, it cannot be used here directly, and I don't want to 
     * reimplement a queue specifically for this case.
     * 
     * Here is the code in cpp:
     * 
     *      if (!root) return;
     *      queue<Node*, int> Q;
     *      Q.push({root, 0});
     *      while (!Q.empty()) {
     *          Node *cur = Q.front().first;
     *          int level = Q.front().second;
     *          cout << "Level " << level << ": " << cur->data << " ";
     *          if (!cur->left)  Q.push({cur->left, level + 1});
     *          if (!cur->right) Q.push({cur->right, level + 1});
     *          Q.pop(); 
     *      }
     */
}

void bst_traverse(Node *root, int mode)
{
    switch (mode) {
    case PRE_ORDER:  
        printf("pre-order: ");
        pre_traverse(root);
        break;

    case IN_ORDER:   
        printf("in-order: ");
        in_traverse(root);
        break;

    case POST_ORDER: 
        printf("post-order: ");
        post_traverse(root);  
        break;

    case LEVEL_ORDER: 
        printf("level-order:\n");
        level_traverse(root);  
        break;

    default:
        printf("wrong mode\n");
        break;
    }
    printf("INVALID \n");
}

int bst_search(Node *root, int data)
{
    if (!root) return FALSE;

    if (data < root->data)
        return bst_search(root->left, data);
    else if (data > root->data)
        return bst_search(root->right, data);
    else
        return TRUE;
}

int bst_find_max(Node *root)
{
    if (!root) return INVALID;

    Node *cur = root;
    while (cur && cur->right)
        cur = cur->right;
    return cur->data;
}

int bst_find_min(Node *root)
{
    if (!root) return INVALID;

    Node *cur = root;
    while (cur && cur->left)
        cur = cur->left;
    return cur->data;
}

int bst_find_height(Node *root)
{
    /* The height of NULL node is -1 */
    if (!root) return -1;

    int left_height = bst_find_height(root->left);
    int right_height = bst_find_height(root->right);
    return MAX(left_height, right_height) + 1;
}

int bst_remove(Node *root, int data)
{

}
