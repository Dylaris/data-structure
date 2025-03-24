#include <criterion/criterion.h>
#include <math.h>
#include "hashtbl.h"

Test(hash_table, test_hashtbl_new_func)
{
    HashTbl *ht = hashtbl_new(5);

    cr_assert_not_null(ht, "hash table should not be null");
    cr_assert_not_null(ht->heads, "hash table heads should not be null");
    cr_assert_eq(ht->size, 5, "hash table size should be %zu", 5);
    cr_assert_eq(ht->count, 0, "hash table count should be 0");
    cr_assert_eq(ht->load_factor, 0, "hash table laod factor should be 0");

    hashtbl_destroy(ht);
}

Test(hash_table, test_is_prime)
{
    cr_assert_eq(is_prime(13),  1, "13 is prime");
    cr_assert_eq(is_prime(14),  0, "14 is not prime");
    cr_assert_eq(is_prime(31),  1, "31 is prime");
    cr_assert_eq(is_prime(123), 0, "123 is not prime");
}

Test(hash_table, test_hash)
{
    HashTbl *ht = hashtbl_new(5);

    cr_assert_eq(hash(ht, "x"), 'x' * (int) pow(31, 0) % ht->size);
    cr_assert_eq(hash(ht, "hello"), ('h' * (int) pow(31, 4) + 
                                     'e' * (int) pow(31, 3) + 
                                     'l' * (int) pow(31, 2) + 
                                     'l' * (int) pow(31, 1) +
                                     'o' * (int) pow(31, 0)) % ht->size);

    hashtbl_destroy(ht);
}

Test(hash_table, test_hashtbl_insert)
{
    HashTbl *ht = hashtbl_new(5);
    size_t count = ht->count;

    hashtbl_insert(&ht, "1", 1); count++;
    hashtbl_insert(&ht, "2", 1); count++;
    hashtbl_insert(&ht, "3", 1); count++;
    hashtbl_insert(&ht, "4", 1); count++;
    hashtbl_insert(&ht, "5", 1); count++;
    hashtbl_insert(&ht, "6", 1); count++;
    cr_assert(ht->count == count, "count should be %d", count);

    hashtbl_insert(&ht, "3", 3);
    hashtbl_insert(&ht, "7", 1); count++;
    hashtbl_insert(&ht, "8", 1); count++;
    cr_assert(ht->count == count, "count should be %d", count);

    hashtbl_destroy(ht);
}

Test(hash_table, test_hashtbl_search)
{
    HashTbl *ht = hashtbl_new(5);

    hashtbl_insert(&ht, "1", 1);
    hashtbl_insert(&ht, "2", 2);
    hashtbl_insert(&ht, "3", 3);
    hashtbl_insert(&ht, "4", 4);
    hashtbl_insert(&ht, "5", 5);
    hashtbl_insert(&ht, "6", 6);
    hashtbl_insert(&ht, "7", 7);
    hashtbl_insert(&ht, "8", 8);

    cr_assert(hashtbl_search(ht, "1") == 1, "<key:1> <value:1>");
    cr_assert(hashtbl_search(ht, "2") == 2, "<key:2> <value:2>");
    cr_assert(hashtbl_search(ht, "7") == 7, "<key:7> <value:7>");
    cr_assert(hashtbl_search(ht, "8") == 8, "<key:8> <value:8>");
    cr_assert(hashtbl_search(ht, "9") == NOT_FOUND, "not found key 9");

    hashtbl_destroy(ht);
}

Test(hash_table, test_hashtbl_delete)
{
    HashTbl *ht = hashtbl_new(5);
    size_t count = 0;

    hashtbl_insert(&ht, "1", 1); count++;
    hashtbl_insert(&ht, "2", 2); count++;
    hashtbl_insert(&ht, "3", 3); count++;
    hashtbl_insert(&ht, "4", 4); count++;
    hashtbl_insert(&ht, "5", 5); count++;
    hashtbl_insert(&ht, "6", 6); count++;
    hashtbl_insert(&ht, "7", 7); count++;
    hashtbl_insert(&ht, "8", 8); count++;
    cr_assert_eq(ht->count, count, "count should be %zu", count);

    hashtbl_delete(&ht, "1"); count--;
    hashtbl_delete(&ht, "2"); count--;
    hashtbl_delete(&ht, "8"); count--;
    hashtbl_delete(&ht, "7"); count--;
    cr_assert_eq(ht->count, count, "count should be %zu", count);
    cr_assert(hashtbl_search(ht, "1") == NOT_FOUND, "not found key 1");
    cr_assert(hashtbl_search(ht, "2") == NOT_FOUND, "not found key 2");
    cr_assert(hashtbl_search(ht, "8") == NOT_FOUND, "not found key 8");
    cr_assert(hashtbl_search(ht, "7") == NOT_FOUND, "not found key 7");
    cr_assert(hashtbl_search(ht, "3") == 3, "<key:3> <value:3>");

    hashtbl_destroy(ht);
}
