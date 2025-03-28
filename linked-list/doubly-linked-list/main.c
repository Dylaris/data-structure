#include "dll.h"
#include <stdio.h>

int main(void)
{
    DoublyLinkedList *dll = dll_new();

    dll_insert(dll, 4);
    dll_insert(dll, 2);
    dll_insert(dll, 1);
    dll_insert(dll, 5);
    dll_insert(dll, 3);
    dll_insert(dll, 6);
    dll_insert(dll, 8);
    dll_insert(dll, 7);
    dll_insert(dll, 9);

    dll_delete(dll, 2);
    dll_delete(dll, 1);
    dll_delete(dll, 3);

    dll_update(dll, 8, 80);
    dll_update(dll, 9, 90);
    dll_update(dll, 10, 100);

    printf("Before reverse: \n");
    dll_print(dll, 0);
    dll_print(dll, 1);

    printf("After reverse: \n");
    dll_reverse(dll);
    dll_print(dll, 0);
    dll_print(dll, 1);

    dll_destroy(dll);

    return 0;
}
