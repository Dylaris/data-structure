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

    ht->heads = malloc(n * sizeof(bucket_t));
    if (ht->heads == NULL) 
        ERR("new hash table buckets");
    for (size_t i = 0; i < n; i++)
        ht->heads[i].next = NULL;

    ht->load_factor = 0;
    ht->count = 0;
    ht->size = n;

    return ht;
}

void hash_destroy(hash_t *ht)
{
    bucket_t *cur, *p;
    for (size_t i = 0; i < ht->size; i++) {
        cur = ht->heads[i].next;
        while (cur != NULL) {
            p = cur;
            cur = cur->next;
            free(p->key);
            free(p);
        }
    }
    free(ht->heads);
    free(ht);
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
    for (size_t i = 0; i < strlen(str); i++)
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
    bucket_t *cur;

    for (size_t i = 0; i < old_size; i++) {
        cur = (*ht)->heads[i].next;
        while (cur != NULL) {
            hash_insert(&new_ht, cur->key, cur->value);
            cur = cur->next;
        }
    }

    hash_destroy(*ht);
    *ht = new_ht;
}

void hash_insert(hash_t **ht, char *key, int val)
{
    int index = hash_func(*ht, key);
    bucket_t *head = (*ht)->heads + index;

    if (head->next == NULL) {
        /* this bucket is unused */
        head->next = malloc(sizeof(bucket_t));
        if (head->next == NULL)
            ERR("add a new bucket at head");
        head->next->key = strdup(key);
        head->next->value = val;
        head->next->next = NULL;
        (*ht)->count++;
    } else {
        bucket_t *cur = head->next, *prev = head;
        int is_update = FALSE;
        while (cur != NULL) {
            if (strcmp(cur->key, key) == 0) {
                /* modify the value */
                cur->value = val;
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
                ERR("add a new bucket at tail");
            cur->key = strdup(key);
            cur->value = val;
            cur->next = NULL;
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
    bucket_t *head = ht->heads + index;
    bucket_t *cur = head->next;

    /* invalid key */
    if (cur == NULL) {
        return NOT_FOUND;
    }

    while (cur != NULL) {
        if (strcmp(cur->key, key) == 0)
            return cur->value;
        cur = cur->next;
    }

    return NOT_FOUND;
}

void hash_delete(hash_t **ht, char *key)
{
    if (hash_search(*ht, key) == NOT_FOUND)
        return;

    int index = hash_func(*ht, key);
    bucket_t *head = (*ht)->heads + index;
    bucket_t *cur = head->next, *prev = head;

    while (cur != NULL) {
        if (strcmp(cur->key, key) == 0) {
            prev->next = cur->next;
            free(cur->key);
            free(cur);
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
