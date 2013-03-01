#include "../include/hash.h"

#define list_elem_to_hash_elem(list_e) \
  list_entry(list_elem, struct hash_elem, list_elem)

bool hash_init(struct hash_table *ht, hash_function *hf,
    less_function *lf, void *aux)
{
  ht->elem_cnt = 0;
  ht->bucket_cnt = DEFAULT_BUCKET_CNT;
  ht->hash = hf;
  ht->less = lf;
  ht->aux = aux;

  ht->buckets = (struct list *)malloc(sizeof(struct list) * ht->bucket_cnt);
  if (ht->buckets != NULL)
  {
    hash_clear(ht, NULL);
    return true;
  }
  else
    return false;
}

void hash_clear(struct hash_table *ht, hash_action *ha)
{
  size_t n;

  for (n = 0; n < ht->bucket_cnt; n++)
  {
   struct list *bucket = &ht->buckets[n];

   if (ha != NULL)
   {
     while(!list_empty(bucket))
     {
      struct list_elem *list_elem = list_pop_front(bucket);
      struct hash_elem *hash_elem = list_elem_to_hash_elem(list_elem);
  
      ha(hash_elem, ht->aux);
     }
   }
  }

  ht->elem_cnt = 0;
}

void hash_destory(struct hash_table *ht, hash_action *ha)
{
  if (ha != NULL)
    hash_clear(ht, ha);
  free(ht->buckets);
}
