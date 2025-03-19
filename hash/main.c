#include "hash.h"

int main(void)
{
    hash_t *ht = hash_new(5);

    hash_insert(&ht, "aaa", 1);
    hash_insert(&ht, "bbb", 2);
    hash_insert(&ht, "ccc", 3);
    hash_insert(&ht, "ddd", 4);
    hash_insert(&ht, "eee", 5);
    hash_insert(&ht, "fff", 6);
    hash_insert(&ht, "ggg", 7);
    hash_insert(&ht, "eee", 8);

    printf("<key: aaa, value: %d\n", hash_search(ht, "aaa"));
    printf("<key: ccc, value: %d\n", hash_search(ht, "ccc"));
    printf("<key: xxx, value: %d\n", hash_search(ht, "xxx"));
    printf("<key: fff, value: %d\n", hash_search(ht, "fff"));
    printf("<key: eee, value: %d\n", hash_search(ht, "eee"));

    hash_delete(&ht, "aaa");
    hash_delete(&ht, "bbb");
    hash_delete(&ht, "ggg");
    hash_delete(&ht, "eee");

    printf("<key: aaa, value: %d\n", hash_search(ht, "aaa"));
    printf("<key: ccc, value: %d\n", hash_search(ht, "ccc"));
    printf("<key: eee, value: %d\n", hash_search(ht, "eee"));

    return 0;
}
