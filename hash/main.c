#include "hash.h"

int main(void)
{
    hash_t *ht = hash_new(5);

    hash_insert(&ht, "1", 1);
    hash_insert(&ht, "2", 2);
    hash_insert(&ht, "3", 3);
    hash_insert(&ht, "4", 4);
    hash_insert(&ht, "5", 5);
    hash_insert(&ht, "6", 6);
    hash_insert(&ht, "7", 7);
    hash_insert(&ht, "8", 8);

    hash_delete(&ht, "1");
    hash_delete(&ht, "2");
    hash_delete(&ht, "8");
    hash_delete(&ht, "7");

    return 0;
}
