#ifndef HASH_H
#define HASH_H

#define ERR(msg) do { \
        fprintf(stderr, "error: %s at <%s:%d>\n", \
            msg, __FILE__, __LINE__); \
        exit(1); \
    } while (0)
#define TRUE  1
#define FALSE 0
#define LOAD_FACTOR_THRESHOLD_UPPER 0.75
#define LOAD_FACTOR_THRESHOLD_LOWER 0.25
#define HASH_EXPAND 0
#define HASH_SHRINK 1

typedef struct pair_tag {
    char *key;
    int value;
} pair_t;

typedef struct bucket_tag {
    struct bucket_tag *next;
    pair_t kv;
} bucket_t;

typedef struct hash_tag {
    bucket_t *buckets;
    float load_factor;
    size_t count; /* number of stored element */
    size_t size;  /* hash allocated space size */
} hash_t;

int is_prime(int n);
hash_t *hash_new(size_t n);
int hash_func(hash_t *hash_tbl, char *str);
void hash_resize(hash_t *hash_tbl, int flag);
void hash_insert(hash_t *hash_tbl, char *key, int val);

#endif /* HASH_H */
