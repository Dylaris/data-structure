#include <criterion/criterion.h>
#include <math.h>
#include "hash.h"

Test(hash_table, test_hash_new_func)
{
    size_t n = 10;
    hash_t *ht = hash_new(n);

    cr_assert_not_null(ht, "hash table should not be null");
    cr_assert_not_null(ht->buckets, "hash table buckets should not be null");
    cr_assert_eq(ht->size, n, "hash table size should be %zu", n);
    cr_assert_eq(ht->count, 0, "hash table count should be 0");
    cr_assert_eq(ht->load_factor, 0, "hash table laod factor should be 0");

    free(ht->buckets);
    free(ht);
}

Test(hash_table, test_is_prime)
{
    cr_assert_eq(is_prime(13),  1, "13 is prime");
    cr_assert_eq(is_prime(14),  0, "14 is not prime");
    cr_assert_eq(is_prime(31),  1, "31 is prime");
    cr_assert_eq(is_prime(123), 0, "123 is not prime");
}

Test(hash_table, test_hash_func)
{
    size_t n = 10;
    hash_t *ht = hash_new(n);

    cr_assert_eq(hash_func(ht, "x"), 'x' * (int) pow(31, 0) % ht->size);
    cr_assert_eq(hash_func(ht, "hello"), ('h' * (int) pow(31, 4) + 
                                          'e' * (int) pow(31, 3) + 
                                          'l' * (int) pow(31, 2) + 
                                          'l' * (int) pow(31, 1) +
                                          'o' * (int) pow(31, 0)) % ht->size);

    free(ht->buckets);
    free(ht);
}

Test(hash_table, test_hash_insert)
{
    size_t n = 10;
    hash_t *ht = hash_new(n);
    size_t count = ht->count;

    hash_insert(ht, "1", 1); count++;
    hash_insert(ht, "2", 1); count++;
    hash_insert(ht, "3", 1); count++;
    cr_assert(ht->count == count, "count should be %d", count);

    hash_insert(ht, "3", 3);
    cr_assert(ht->count == count, "count should be %d", count);

    free(ht->buckets);
    free(ht);
}
