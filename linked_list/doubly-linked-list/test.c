#include "dll.h"
#include <criterion/criterion.h>

#define TEST_PRINT 0

Test(doubly_linked_list, test_dll_new)
{
    DoublyLinkedList *dll = dll_new();

    cr_assert_eq(dll->size, 0, "size of dll should be 0");
    cr_assert_eq(dll->dummy_head.data, INVALID_DATA);
    cr_assert_eq(dll->dummy_head.next, &dll->dummy_tail);
    cr_assert_eq(dll->dummy_head.prev, NULL);
    cr_assert_eq(dll->dummy_tail.data, INVALID_DATA);
    cr_assert_eq(dll->dummy_tail.next, NULL);
    cr_assert_eq(dll->dummy_tail.prev, &dll->dummy_head);

    dll_destroy(dll);
}

Test(doubly_linked_list, test_dll_insert)
{
    DoublyLinkedList *dll = dll_new();
    size_t count = 0;

    dll_insert(dll, 4); count++;
    dll_insert(dll, 2); count++;
    dll_insert(dll, 1); count++;
    dll_insert(dll, 5); count++;
    dll_insert(dll, 3); count++;
    dll_insert(dll, 6); count++;

    cr_assert_eq(dll->size, count, "the size of dll should be %d", count);
#if TEST_PRINT == 1
    dll_print(dll, 0);
    dll_print(dll, 1);
#endif

    dll_destroy(dll);
}

Test(doubly_linked_list, test_dll_delete)
{
    DoublyLinkedList *dll = dll_new();
    size_t count = 0;

    dll_insert(dll, 4); count++;
    dll_insert(dll, 2); count++;
    dll_insert(dll, 1); count++;
    dll_insert(dll, 5); count++;
    dll_insert(dll, 3); count++;
    dll_insert(dll, 6); count++;
    dll_insert(dll, 8); count++;
    dll_insert(dll, 7); count++;
    dll_insert(dll, 9); count++;

    cr_assert_eq(dll->size, count, "the size of dll should be %d", count);
#if TEST_PRINT == 1
    dll_print(dll, 0);
    dll_print(dll, 1);
#endif

    dll_delete(dll, 2); count--;
    dll_delete(dll, 1); count--;
    dll_delete(dll, 6); count--;
    dll_delete(dll, 7); count--;
    dll_delete(dll, 9); count--;

    cr_assert_eq(dll->size, count, "the size of dll should be %d", count);
#if TEST_PRINT == 1
    dll_print(dll, 0);
    dll_print(dll, 1);
#endif

    dll_destroy(dll);
}

Test(doubly_linked_list, test_dll_search)
{
    DoublyLinkedList *dll = dll_new();
    size_t count = 0;

    dll_insert(dll, 4); count++;
    dll_insert(dll, 2); count++;
    dll_insert(dll, 1); count++;
    dll_insert(dll, 5); count++;
    dll_insert(dll, 3); count++;
    dll_insert(dll, 6); count++;

    cr_assert_eq(dll->size, count, "the size of dll should be %d", count);
#if TEST_PRINT == 1
    dll_print(dll, 0);
    dll_print(dll, 1);
#endif

    Node *node = dll_search(dll, 10);
    cr_assert_eq(node, NULL, "10 should be a invalid data in this dll");

    node = dll_search(dll, 1);
    cr_assert_eq(node->data, 1, "search 1");
    cr_assert_eq(node->next->data, 2, "next should be 2");

    node = dll_search(dll, 3);
    cr_assert_eq(node->data, 3, "search 3");
    cr_assert_eq(node->next->data, 4, "next should be 4");

    node = dll_search(dll, 6);
    cr_assert_eq(node->data, 6, "search 6");
    cr_assert_eq(node->next, &dll->dummy_tail, "next should be dummy tail");

    dll_destroy(dll);
}

Test(doubly_linked_list, test_dll_update)
{
    DoublyLinkedList *dll = dll_new();
    size_t count = 0;

    dll_insert(dll, 4); count++;
    dll_insert(dll, 2); count++;
    dll_insert(dll, 1); count++;
    dll_insert(dll, 5); count++;
    dll_insert(dll, 3); count++;
    dll_insert(dll, 6); count++;

    cr_assert_eq(dll->size, count, "the size of dll should be %d", count);
#if TEST_PRINT == 1
    dll_print(dll, 0);
    dll_print(dll, 1);
#endif

    dll_update(dll, 6, 9);
    dll_update(dll, 1, 10); 
    dll_update(dll, 5, 6);
    dll_update(dll, 100, 12);
    cr_assert_eq(dll->size, count, "the size of dll should be %d", count);
#if TEST_PRINT == 1
    dll_print(dll, 0);
    dll_print(dll, 1);
#endif

    dll_destroy(dll);
}

Test(doubly_linked_list, test_dll_reverse)
{
    DoublyLinkedList *dll = dll_new();
    size_t count = 0;

    dll_insert(dll, 4); count++;
    dll_insert(dll, 2); count++;
    dll_insert(dll, 1); count++;
    dll_insert(dll, 5); count++;
    dll_insert(dll, 3); count++;
    dll_insert(dll, 6); count++;
    cr_assert_eq(dll->size, count, "the size of dll should be %d", count);

    dll_reverse(dll);
    cr_assert_eq(dll->size, count, "the size of dll should be %d", count);
    cr_assert_eq(dll->dummy_head.prev, NULL);
    cr_assert_eq(dll->dummy_head.next->data, 6);
    cr_assert_eq(dll->dummy_tail.next, NULL);
    cr_assert_eq(dll->dummy_tail.prev->data, 1);
#if TEST_PRINT == 1
    dll_print(dll, 0);
    dll_print(dll, 1);
#endif

    dll_destroy(dll);
}
