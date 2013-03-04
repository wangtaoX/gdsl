#include "../include/hash.h"

#define list_elem_to_hash_elem(list_e) \
  list_entry(list_e, struct hash_elem, list_elem)

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
   list_init(bucket);
  }

  ht->elem_cnt = 0;
}

void hash_destory(struct hash_table *ht, hash_action *ha)
{
  if (ha != NULL)
    hash_clear(ht, ha);
  free(ht->buckets);
}

bool hash_empty(struct hash_table *ht)
{
  return ((ht != NULL) && ht->elem_cnt == 0);
}

size_t hash_size(struct hash_table *ht)
{
  return ht->elem_cnt;
}

/* find an ELEMENT equal to HE and return it, otherwise return NULL */
struct hash_elem *find_elem(struct hash_table *ht, struct list *list, struct hash_elem *he)
{
  struct list_elem *le;

  /* 1. walk through the list and find the ELEMENT,
   * maybe there is no such ELEMENT */
  if (list == NULL || he == NULL || ht == NULL)
    return NULL;

  /* #### here comes a BUG */
  for (le = list_begin(list); le != list_tail(list); le = list_next(le))
  {
    struct hash_elem *h = list_elem_to_hash_elem(le);
    if (!ht->less(he, h, ht->aux) && !ht->less(h, he, ht->aux))
      return h;
  }

  /* no such element */
  return NULL;
}

/* find the bucket id for element HE */
static struct list *find_bucket(struct hash_table *ht, struct hash_elem *he)
{
  /* 1. find bucket id
   * 2. return the address of the list by bucket id */
  size_t bucket_id = ht->hash(he, ht->aux) & (ht->bucket_cnt - 1);
  printf("bucket_id %d\n", bucket_id);
  return &ht->buckets[bucket_id];
}

/* remove HE from hash table */
void remove_elem(struct hash_table *ht, struct hash_elem *he)
{
  ht->elem_cnt--;
  list_remove(&he->list_elem);
}

/* insert HE into list BUCKET */
void insert_elem(struct hash_table *ht, struct list *list, struct hash_elem *he)
{
  ht->elem_cnt++;
  list_push_front(list, &he->list_elem);
}

/* return NULL if there is an ELEMENT equal to HE, 
 * otherwise return itself */
struct hash_elem *hash_insert(struct hash_table *ht, struct hash_elem *he)
{
  /* 1. find bucket
   * 2. is there an element equal to HE ?
   * 3. find an element , then return NULL
   * 4. wether rehash the hash table */
  struct list *bucket = find_bucket(ht, he);
  struct hash_elem *hash_elem = find_elem(ht, bucket, he);

  if (hash_elem == NULL)
  {
    insert_elem(ht, bucket, he);
    printf("insert\n");
  }

  return hash_elem;
}

/* return the number of elements in each buckets */
size_t hash_each_size(struct hash_table *ht, size_t bucket_id)
{
  struct list *list = &ht->buckets[bucket_id];

  return (!list_empty(list) ? list_size(list) : 0);
}

/* return the number of buckets in hash table HT */
size_t hash_buckets(struct hash_table *ht)
{
  return ht->bucket_cnt;
}

/* find HE in hash table */
struct hash_elem *hash_find(struct hash_table *ht,
    struct hash_elem *he)
{
  return find_elem(ht, find_bucket(ht, he), he);
}

/* replace a given element equal to he */
struct hash_elem *hash_replace(struct hash_table *ht, 
    struct hash_elem *he)
{
  struct list *bucket = find_bucket(ht, he);
  struct hash_elem *hash_elem = find_elem(ht, bucket, he);

  if (hash_elem != NULL)
  {
    remove_elem(ht, hash_elem);
  }

  insert_elem(ht, bucket, he);

  return hash_elem;
}

/* delete HE from hash table */
struct hash_elem *hash_delete(struct hash_table *ht, 
    struct hash_elem *he)
{
  struct hash_elem *hash_elem = find_elem(ht, find_bucket(ht, he), he);

  if (hash_elem != NULL)
  {
    remove_elem(ht, hash_elem);
  }

  return hash_elem;
}
