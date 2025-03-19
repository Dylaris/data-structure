/*
 * Using chaining method to handle collision.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "hash.h"

hash_t *hash_new(size_t n)
{
    hash_t *ht = malloc(sizeof(hash_t));
    if (ht == NULL) 
        ERR("new hash table");

    ht->buckets = malloc(n * sizeof(bucket_t));
    if (ht->buckets == NULL) 
        ERR("new hash table buckets");

    ht->load_factor = 0;
    ht->count = 0;
    ht->size = n;

    return ht;
}

int is_prime(int n)
{
    int n_sqrt = (int) sqrt(n);
    for (int i = 2; i < n_sqrt; i++)
        if (n % i == 0) return FALSE;
    return TRUE;
}

int hash_func(hash_t *ht, char *str)
{
    long n = 0;
    for (int i = 0; i < strlen(str); i++)
        n = n * 31 + (long) str[i];
    return (int) (n % ht->size);
}

void hash_resize(hash_t *ht, int flag)
{
    if (flag == HASH_EXPAND) {
        /* expand */
    } else {
        /* shrink */
    }
}

void hash_insert(hash_t *ht, char *key, int val)
{
    int index = hash_func(ht, key);
    bucket_t *bucket = ht->buckets + index;

    if (bucket->kv.key == NULL) {
        /* this bucket is unused */
        bucket->kv.value = val;
        bucket->kv.key = strdup(key);
        ht->count++;
    } else {
        bucket_t *cur = bucket, *prev = NULL;
        int is_update = FALSE;
        while (cur != NULL) {
            if (strcmp(cur->kv.key, key) == 0) {
                /* modify the value */
                cur->kv.value = val;
                is_update = TRUE;
                break;
            }
            prev = cur;
            cur = cur->next;
        }
        if (is_update == FALSE) {
            /* add the key-value */
            cur = malloc(sizeof(bucket_t));
            if (cur == NULL)
                ERR("append bucket");
            cur->next = NULL;
            cur->kv.key = strdup(key);
            cur->kv.value = val;
            prev->next = cur;
            ht->count++;
        }
    }

    ht->load_factor = (float) ht->count / (float) ht->size;
    if (ht->load_factor > LOAD_FACTOR_THRESHOLD_UPPER)
        hash_resize(ht, HASH_EXPAND);
    else if (ht->load_factor < LOAD_FACTOR_THRESHOLD_LOWER)
        hash_resize(ht, HASH_SHRINK);
}
