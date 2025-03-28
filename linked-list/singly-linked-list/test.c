#include "sll.h"
#include <criterion/criterion.h>

#define TEST_PRINT 0

Test(singly_linked_list, test_sll_new)
{
    SinglyLinkedList *sll = sll_new();

    cr_assert_eq(sll->size, 0, "size of sll should be 0");
    cr_assert_eq(sll->dummy_head.data, INVALID_DATA, "data of dummy head should be -1");
    cr_assert_eq(sll->dummy_head.next, NULL, "next of dummy head should be NULL");

    sll_destroy(sll);
}

Test(singly_linked_list, test_sll_insert)
{
    SinglyLinkedList *sll = sll_new();
    size_t count = 0;

    sll_insert(sll, 4); count++;
    sll_insert(sll, 2); count++;
    sll_insert(sll, 1); count++;
    sll_insert(sll, 5); count++;
    sll_insert(sll, 3); count++;
    sll_insert(sll, 6); count++;

    cr_assert_eq(sll->size, count, "the size of sll should be %d", count);
#if TEST_PRINT == 1
    sll_print(sll);
#endif

    sll_destroy(sll);
}

Test(singly_linked_list, test_sll_delete)
{
    SinglyLinkedList *sll = sll_new();
    size_t count = 0;

    sll_insert(sll, 4); count++;
    sll_insert(sll, 2); count++;
    sll_insert(sll, 1); count++;
    sll_insert(sll, 5); count++;
    sll_insert(sll, 3); count++;
    sll_insert(sll, 6); count++;
    sll_insert(sll, 8); count++;
    sll_insert(sll, 7); count++;
    sll_insert(sll, 9); count++;

    cr_assert_eq(sll->size, count, "the size of sll should be %d", count);
#if TEST_PRINT == 1
    sll_print(sll);
#endif

    sll_delete(sll, 2); count--;
    sll_delete(sll, 1); count--;
    sll_delete(sll, 6); count--;
    sll_delete(sll, 7); count--;
    sll_delete(sll, 9); count--;

    cr_assert_eq(sll->size, count, "the size of sll should be %d", count);
#if TEST_PRINT == 1
    sll_print(sll);
#endif

    sll_destroy(sll);
}

Test(singly_linked_list, test_sll_search)
{
    SinglyLinkedList *sll = sll_new();
    size_t count = 0;

    sll_insert(sll, 4); count++;
    sll_insert(sll, 2); count++;
    sll_insert(sll, 1); count++;
    sll_insert(sll, 5); count++;
    sll_insert(sll, 3); count++;
    sll_insert(sll, 6); count++;

    cr_assert_eq(sll->size, count, "the size of sll should be %d", count);
#if TEST_PRINT == 1
    sll_print(sll);
#endif

    Node *node = sll_search(sll, 10);
    cr_assert_eq(node, NULL, "10 should be a invalid data in this sll");

    node = sll_search(sll, 1);
    cr_assert_eq(node->data, 1, "search 1");
    cr_assert_eq(node->next->data, 2, "next should be 2");

    node = sll_search(sll, 3);
    cr_assert_eq(node->data, 3, "search 3");
    cr_assert_eq(node->next->data, 4, "next should be 4");

    node = sll_search(sll, 6);
    cr_assert_eq(node->data, 6, "search 6");
    cr_assert_eq(node->next, NULL, "next should be NULL");

    sll_destroy(sll);
}

Test(singly_linked_list, test_sll_update)
{
    SinglyLinkedList *sll = sll_new();
    size_t count = 0;

    sll_insert(sll, 4); count++;
    sll_insert(sll, 2); count++;
    sll_insert(sll, 1); count++;
    sll_insert(sll, 5); count++;
    sll_insert(sll, 3); count++;
    sll_insert(sll, 6); count++;

    cr_assert_eq(sll->size, count, "the size of sll should be %d", count);
#if TEST_PRINT == 1
    sll_print(sll);
#endif

    sll_update(sll, 6, 9);
    sll_update(sll, 1, 10); 
    sll_update(sll, 5, 6);
    sll_update(sll, 100, 12);
    cr_assert_eq(sll->size, count, "the size of sll should be %d", count);
#if TEST_PRINT == 1
    sll_print(sll);
#endif

    sll_destroy(sll);
}

Test(singly_linked_list, test_sll_reverse)
{
    SinglyLinkedList *sll = sll_new();
    size_t count = 0;

    sll_insert(sll, 4); count++;
    sll_insert(sll, 2); count++;
    sll_insert(sll, 1); count++;
    sll_insert(sll, 5); count++;
    sll_insert(sll, 3); count++;
    sll_insert(sll, 6); count++;
    cr_assert_eq(sll->size, count, "the size of sll should be %d", count);
#if TEST_PRINT == 1
    sll_print(sll);
#endif

    sll_reverse(sll);
    cr_assert_eq(sll->size, count, "the size of sll should be %d", count);
#if TEST_PRINT == 1
    sll_print(sll);
#endif

    sll_destroy(sll);
}
