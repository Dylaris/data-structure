/*
 * Using chaining method to handle collision.
 */

#include <stdlib.h>
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
    for (size_t i = 0; i < n; i++) {
        ht->buckets[i].kv.key = NULL;
        ht->buckets[i].kv.value = INVALID;
    }

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

void hash_resize(hash_t **ht, int flag)
{
    size_t new_size, old_size = (*ht)->size;

    if (flag == HASH_EXPAND) {
        /* expand */
        new_size = old_size * 2;
    } else {
        /* shrink */
        new_size = old_size / 2;
    }

    hash_t *new_ht = hash_new(new_size);
    bucket_t *bucket;

    for (size_t i = 0; i < old_size; i++) {
        bucket = &(*ht)->buckets[i];
        while (bucket != NULL && bucket->kv.key != NULL) {
            hash_insert(&new_ht, bucket->kv.key, bucket->kv.value);
            bucket = bucket->next;
        }
    }

    *ht = new_ht;
}

void hash_insert(hash_t **ht, char *key, int val)
{
    int index = hash_func(*ht, key);
    bucket_t *bucket = (*ht)->buckets + index;

    if (bucket->kv.key == NULL) {
        /* this bucket is unused */
        bucket->kv.value = val;
        bucket->kv.key = strdup(key);
        (*ht)->count++;
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
            (*ht)->count++;
        }
    }

    (*ht)->load_factor = (float) (*ht)->count / (float) (*ht)->size;
    if ((*ht)->load_factor > LOAD_FACTOR_THRESHOLD_UPPER)
        hash_resize(ht, HASH_EXPAND);
}

int hash_search(hash_t *ht, char *key)
{
    int index = hash_func(ht, key);
    bucket_t *bucket = ht->buckets + index;

    /* invalid key */
    if (bucket->kv.key == NULL) {
        return INVALID;
    }

    while (bucket != NULL) {
        if (strcmp(bucket->kv.key, key) == 0)
            return bucket->kv.value;
        bucket = bucket->next;
    }

    return INVALID;
}

void hash_delete(hash_t **ht, char *key)
{
    if (hash_search(*ht, key) == INVALID)
        return;

    int index = hash_func(*ht, key);
    bucket_t *bucket = (*ht)->buckets + index;

    bucket_t *cur = bucket, *prev = NULL;
    while (cur != NULL) {
        if (strcmp(cur->kv.key, key) == 0) {
            if (prev == NULL) {
                /* copy the next into the head if it exists */
                free(cur->kv.key);
                cur->kv.key = NULL;
                bucket_t *next = cur->next;
                if (next != NULL) {
                    cur->kv.key = strdup(next->kv.key);
                    cur->kv.value = next->kv.value;
                    cur->next = next->next;
                    free(next->kv.key);
                    free(next);
                }
            } else {
                prev->next = cur->next;
                free(cur->kv.key);
                free(cur); 
            }
            (*ht)->count--;
            break;
        }
        prev = cur;
        cur = cur->next;
    }

    (*ht)->load_factor = (float) (*ht)->count / (float) (*ht)->size;
    if ((*ht)->load_factor < LOAD_FACTOR_THRESHOLD_LOWER)
        hash_resize(ht, HASH_SHRINK);
}
