#include <criterion/criterion.h>
#include <criterion/logging.h>
#include <math.h>
#include "hash.h"

Test(hash_table, test_hash_new_func)
{
    hash_t *ht = hash_new(5);

    cr_assert_not_null(ht, "hash table should not be null");
    cr_assert_not_null(ht->buckets, "hash table buckets should not be null");
    cr_assert_eq(ht->size, 5, "hash table size should be %zu", 5);
    cr_assert_eq(ht->count, 0, "hash table count should be 0");
    cr_assert_eq(ht->load_factor, 0, "hash table laod factor should be 0");
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
    hash_t *ht = hash_new(5);

    cr_assert_eq(hash_func(ht, "x"), 'x' * (int) pow(31, 0) % ht->size);
    cr_assert_eq(hash_func(ht, "hello"), ('h' * (int) pow(31, 4) + 
                                          'e' * (int) pow(31, 3) + 
                                          'l' * (int) pow(31, 2) + 
                                          'l' * (int) pow(31, 1) +
                                          'o' * (int) pow(31, 0)) % ht->size);
}

Test(hash_table, test_hash_insert)
{
    hash_t *ht = hash_new(5);
    size_t count = ht->count;

    hash_insert(&ht, "1", 1); count++;
    hash_insert(&ht, "2", 1); count++;
    hash_insert(&ht, "3", 1); count++;
    hash_insert(&ht, "4", 1); count++;
    hash_insert(&ht, "5", 1); count++;
    hash_insert(&ht, "6", 1); count++;
    cr_assert(ht->count == count, "count should be %d", count);

    hash_insert(&ht, "3", 3);
    hash_insert(&ht, "7", 1); count++;
    hash_insert(&ht, "8", 1); count++;
    cr_assert(ht->count == count, "count should be %d", count);
}

Test(hash_table, test_hash_search)
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

    cr_assert(hash_search(ht, "1") == 1, "<key:1> <value:1>");
    cr_assert(hash_search(ht, "2") == 2, "<key:2> <value:2>");
    cr_assert(hash_search(ht, "7") == 7, "<key:7> <value:7>");
    cr_assert(hash_search(ht, "8") == 8, "<key:8> <value:8>");
    cr_assert(hash_search(ht, "9") == INVALID, "invalid key 9");
}

Test(hash_table, test_hash_delete)
{
    hash_t *ht = hash_new(5);
    size_t count = 0;

    hash_insert(&ht, "1", 1); count++;
    hash_insert(&ht, "2", 2); count++;
    hash_insert(&ht, "3", 3); count++;
    hash_insert(&ht, "4", 4); count++;
    hash_insert(&ht, "5", 5); count++;
    hash_insert(&ht, "6", 6); count++;
    hash_insert(&ht, "7", 7); count++;
    hash_insert(&ht, "8", 8); count++;
    cr_assert_eq(ht->count, count, "count should be %zu", count);

    hash_delete(&ht, "1"); count--;
    hash_delete(&ht, "2"); count--;
    hash_delete(&ht, "8"); count--;
    hash_delete(&ht, "7"); count--;
    cr_assert_eq(ht->count, count, "count should be %zu", count);
    cr_assert(hash_search(ht, "1") == INVALID, "invalid key 1");
    cr_assert(hash_search(ht, "2") == INVALID, "invalid key 2");
    cr_assert(hash_search(ht, "8") == INVALID, "invalid key 8");
    cr_assert(hash_search(ht, "7") == INVALID, "invalid key 7");
    cr_assert(hash_search(ht, "3") == 3, "<key:3> <value:3>");
}
