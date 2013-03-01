#ifndef __HASH_H
#define __HASH_H

#include <stdint.h>
#include <stdbool.h>
#include  <stddef.h>
#include <stdlib.h>
#include "list.h"

#define DEFAULT_BUCKET_CNT 4

struct hash_elem 
{
  struct list_elem list_elem;
};

/* it sames like the linux kernel list */
#define hash_entry(HASH_ELEM, STRUCT, MEMBER)       \
  ((STRUCT*) ((uint8_t *) &(HASH_ELEM)->list_elem    \
    - offsetof(STRUCT, MEMBER.list_elem)))

/* hash function */
typedef unsigned hash_function(const struct hash_elem *hash_elem, void *aux);
/* hash less function */
typedef bool less_function(const struct hash_elem *hash_elem1,
                           const struct hash_elem *hash_elem2,
                           void *aux);
/* operation on hash element */
typedef void hash_action(struct hash_elem *hash_elem, void *aux);

/* hash table */
struct hash_table
{
  size_t elem_cnt; /* number of elements in hash table */
  size_t bucket_cnt;
  struct list *buckets;
  hash_function *hash; /* hash function */
  less_function *less; 
  void *aux;     
};

/* basic operation on hash table */
bool hash_init(struct hash_table *ht, hash_function *hf, 
    less_function *lf, void *aux);
void hash_clear(struct hash_table *ht, hash_action *ha);
void hash_destory(struct hash_table *ht, hash_action *ha);

/* hash table information */
bool hash_empty(struct hash_table *ht);
size_t hash_size(struct hash_table *ht);

/* hash table operation */
struct hash_elem *hash_insert(struct hash_table *ht, struct hash_elem *he);
#endif
