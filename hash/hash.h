#ifndef HASH_H
#define HASH_H

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
#define HASH_EXPAND 1
#define HASH_SHRINK 0
#define NOT_FOUND -1

typedef struct bucket_tag {
    struct bucket_tag *next;
    char *key;
    int value;
} bucket_t;

typedef struct hash_tag {
    bucket_t *heads;    /* dummy head for bucket list */
    float load_factor;
    size_t count;       /* number of stored element */
    size_t size;        /* hash allocated space size */
} hash_t;

int is_prime(int n);
hash_t *hash_new(size_t n);
void hash_destroy(hash_t *ht);
int hash_func(hash_t *ht, char *str);
void hash_resize(hash_t **ht, int flag);
void hash_insert(hash_t **ht, char *key, int val);
int hash_search(hash_t *ht, char *key);
void hash_delete(hash_t **ht, char *key);

#endif /* HASH_H */
