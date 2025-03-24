#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "hashtbl.h"

HashTbl *hashtbl_new(size_t n)
{
    HashTbl *ht = malloc(sizeof(HashTbl));
    if (ht == NULL) 
        ERR("new hash table");

    ht->heads = malloc(n * sizeof(Bucket));
    if (ht->heads == NULL) 
        ERR("new hash table buckets");
    for (size_t i = 0; i < n; i++)
        ht->heads[i].next = NULL;

    ht->load_factor = 0;
    ht->count = 0;
    ht->size = n;

    return ht;
}

void hashtbl_destroy(HashTbl *ht)
{
    Bucket *cur, *p;
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

int hash(HashTbl *ht, char *str)
{
    long n = 0;
    for (size_t i = 0; i < strlen(str); i++)
        n = n * PRIME + (long) str[i];
    return (int) (n % ht->size);
}

void hashtbl_resize(HashTbl **ht, int flag)
{
    size_t new_size, old_size = (*ht)->size;

    if (flag == HASHTBL_EXPAND) {
        /* expand */
        new_size = old_size * 2;
    } else {
        /* shrink */
        new_size = old_size / 2;
    }

    HashTbl *new_ht = hashtbl_new(new_size);
    Bucket *cur;

    for (size_t i = 0; i < old_size; i++) {
        cur = (*ht)->heads[i].next;
        while (cur != NULL) {
            hashtbl_insert(&new_ht, cur->key, cur->value);
            cur = cur->next;
        }
    }

    hashtbl_destroy(*ht);
    *ht = new_ht;
}

void hashtbl_insert(HashTbl **ht, char *key, int val)
{
    int index = hash(*ht, key);
    Bucket *head = (*ht)->heads + index;

    if (head->next == NULL) {
        /* this bucket is unused */
        head->next = malloc(sizeof(Bucket));
        if (head->next == NULL)
            ERR("add a new bucket at head");
        head->next->key = strdup(key);
        head->next->value = val;
        head->next->next = NULL;
        (*ht)->count++;
    } else {
        Bucket *cur = head->next, *prev = head;
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
            cur = malloc(sizeof(Bucket));
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
        hashtbl_resize(ht, HASHTBL_EXPAND);
}

int hashtbl_search(HashTbl *ht, char *key)
{
    int index = hash(ht, key);
    Bucket *head = ht->heads + index;
    Bucket *cur = head->next;

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

void hashtbl_delete(HashTbl **ht, char *key)
{
    if (hashtbl_search(*ht, key) == NOT_FOUND)
        return;

    int index = hash(*ht, key);
    Bucket *head = (*ht)->heads + index;
    Bucket *cur = head->next, *prev = head;

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
        hashtbl_resize(ht, HASHTBL_SHRINK);
}
