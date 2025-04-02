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

Node *bst_insert(Node *root, int data)
{
    if (!root)
        root = new_node(data);
    else if (data <= root->data)
        root->left = bst_insert(root->left, data);
    else
        root->right = bst_insert(root->right, data);

    return root;
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

Node *bst_search(Node *root, int data)
{
    if (!root) return NULL;

    if (data < root->data)
        return bst_search(root->left, data);
    else if (data > root->data)
        return bst_search(root->right, data);
    else
        return root;
}

Node *bst_find_max(Node *root)
{
    if (!root) return NULL;

    Node *cur = root;
    while (cur && cur->right)
        cur = cur->right;
    return cur;
}

Node *bst_find_min(Node *root)
{
    if (!root) return NULL;

    Node *cur = root;
    while (cur && cur->left)
        cur = cur->left;
    return cur;
}

int bst_find_height(Node *root)
{
    /* The height of NULL node is -1 */
    if (!root) return -1;

    int left_height = bst_find_height(root->left);
    int right_height = bst_find_height(root->right);
    return MAX(left_height, right_height) + 1;
}

Node *bst_remove(Node *root, int data)
{
    if (!root) return NULL;
    else if (data < root->data) root->left = bst_remove(root->left, data);
    else if (data > root->data) root->right = bst_remove(root->right, data);
    else { /* Find the delete node */
        if (!root->left && !root->right) {
            /* CASE1: no child */
            free(root);
            root = NULL;
        } else if (!root->left) {
            /* CASE2: one child (right node) */
            Node *tmp = root;
            root = root->right;
            free(tmp);
        } else if (!root->right) {
            /* CASE2: one child (left node) */
            Node *tmp = root;
            root = root->left;
            free(tmp);
        } else {
            /* CASE3: two children */
            Node *tmp = bst_find_min(root->right);
            root->data = tmp->data;
            root->right = bst_remove(root->right, tmp->data);

            /*
             * NOTE: two ways in CASE3
             * 1. 
             *    find min data from right-subtree
             *    copy the value in targetted node
             *    delete duplicate from right-subtree
             * 2.
             *    find max data from left-subtree
             *    copy the value in targetted node
             *    delete duplicate from left-subtree
             */
        }
    }
    return root;
}

/*
 * Every node execept root has a limit -> (min, max]
 */
static int is_bst_util(Node *root, int min, int max)
{
    if (!root) return TRUE;

    if (root->data > min && root->data <= max &&
        is_bst_util(root->left, min, root->data) &&
        is_bst_util(root->right, root->data, max))
        return TRUE;
    return FALSE;
}

int bst_verify(Node *root)
{
    return is_bst_util(root, -2147483648, 2147483647);
}

/*
 * Get the successor of given node in in-order traverse.
 */
Node *bst_get_successor(Node *root, int data)
{
    Node *cur = bst_search(root, data);
    if (!cur) return NULL;

    if (cur->right) {
        /* CASE1: node has right-subtree */
        return bst_find_min(cur->right);
    } else {
        /* CASE2: no right-subtree */
        Node *successor = NULL;
        Node *ancestor = root;
        while (ancestor != cur) {
            if (cur->data <= ancestor->data) {
                successor = ancestor;   /* So far this is the deepest node for which current node is in left */
                ancestor = ancestor->left;
            } else {
                ancestor = ancestor->right;
            }
        }
        return successor;
    }
}
