/*
 * This code implements methods for a hash table, 
 * which uses seperate chaining to handle collisions.
 */

#ifndef HASHTBL_H
#define HASHTBL_H

#include <stdio.h>

#define ERR(msg) do { \
        fprintf(stderr, "error: %s at <%s:%d>\n", \
            msg, __FILE__, __LINE__); \
        exit(1); \
    } while (0)
#define TRUE  1
#define FALSE 0
#define LOAD_FACTOR_THRESHOLD_UPPER 0.75
#define LOAD_FACTOR_THRESHOLD_LOWER 0.25
#define HASHTBL_EXPAND 1
#define HASHTBL_SHRINK 0
#define NOT_FOUND -1
#define PRIME 31

typedef struct Bucket {
    struct Bucket *next;
    char *key;
    int value;
} Bucket;

typedef struct HashTbl {
    Bucket *heads;      /* dummy head for bucket list */
    float load_factor;
    size_t count;       /* number of stored element */
    size_t size;        /* hash allocated space size */
} HashTbl;

int is_prime(int n);
HashTbl *hashtbl_new(size_t n);
void hashtbl_destroy(HashTbl *ht);
int hash(HashTbl *ht, char *str);
void hashtbl_resize(HashTbl **ht, int flag);
void hashtbl_insert(HashTbl **ht, char *key, int val);
int hashtbl_search(HashTbl *ht, char *key);
void hashtbl_delete(HashTbl **ht, char *key);

#endif /* HASHTBL_H */
