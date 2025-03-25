#include "sll.h"

int main(void)
{
    SinglyLinkedList *sll = sll_new();

    sll_insert(sll, 4);
    sll_insert(sll, 2);
    sll_insert(sll, 1);
    sll_insert(sll, 5);
    sll_insert(sll, 3);
    sll_insert(sll, 6);
    sll_insert(sll, 8);
    sll_insert(sll, 7);
    sll_insert(sll, 9);

    sll_delete(sll, 2);
    sll_delete(sll, 1);
    sll_delete(sll, 3);

    sll_update(sll, 8, 80);
    sll_update(sll, 9, 90);
    sll_update(sll, 10, 100);

    sll_reverse(sll);

    sll_print(sll);

    sll_destroy(sll);

    return 0;
}
