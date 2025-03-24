#include "hashtbl.h"

int main(void)
{
    HashTbl *ht = hashtbl_new(5);

    hashtbl_insert(&ht, "aaa", 1);
    hashtbl_insert(&ht, "bbb", 2);
    hashtbl_insert(&ht, "ccc", 3);
    hashtbl_insert(&ht, "ddd", 4);
    hashtbl_insert(&ht, "eee", 5);
    hashtbl_insert(&ht, "fff", 6);
    hashtbl_insert(&ht, "ggg", 7);
    hashtbl_insert(&ht, "eee", 8);

    printf("<key: aaa, value: %2d>\n", hashtbl_search(ht, "aaa"));
    printf("<key: ccc, value: %2d>\n", hashtbl_search(ht, "ccc"));
    printf("<key: xxx, value: %2d>\n", hashtbl_search(ht, "xxx"));
    printf("<key: fff, value: %2d>\n", hashtbl_search(ht, "fff"));
    printf("<key: eee, value: %2d>\n", hashtbl_search(ht, "eee"));

    hashtbl_delete(&ht, "aaa");
    hashtbl_delete(&ht, "bbb");
    hashtbl_delete(&ht, "ggg");
    hashtbl_delete(&ht, "eee");

    printf("<key: aaa, value: %2d>\n", hashtbl_search(ht, "aaa"));
    printf("<key: ccc, value: %2d>\n", hashtbl_search(ht, "ccc"));
    printf("<key: eee, value: %2d>\n", hashtbl_search(ht, "eee"));

    hashtbl_destroy(ht);

    return 0;
}
