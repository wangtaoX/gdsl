#include "../include/hash.h"
#include <string.h>

typedef struct my_s
{
  char str[20];
  struct hash_elem hash_elem;
}my_s;

unsigned hash_djb2(unsigned char *str)
{
  unsigned long hash = 5381;
  int c;

  while(c = *str++)
    hash = ((hash << 5) + hash) + c;

  return hash;
}
unsigned hash_string(const struct hash_elem *he, void *aux)
{
  struct my_s *ms =  hash_entry(he, struct my_s, hash_elem);
  unsigned char *x = (unsigned char *)(ms->str);

  return hash_djb2(x);
}
bool hash_less(const struct hash_elem *h1, 
               const struct hash_elem *h2,
               void *aux)
{
  struct my_s *h1_ = hash_entry(h1, struct my_s, hash_elem);
  struct my_s *h2_ = hash_entry(h2, struct my_s, hash_elem);
  
  char *str1 = h1_->str, *str2 = h2_->str;
  while(*str1 != '\n' || *str2 != '\n')
  {
    if (*str1 != *str2)
      return *str1 < *str2;
    else
    {
      str1++;
      str2++;
    }
  }

  if (*str1 == *str2)
    return false;
  if( *str1 == '\n' && *str1 != *str2)
    return true;
  
  return false;
}

int main()
{
  my_s *s;
  struct hash_table ht;
  int cnt = 0;

  hash_init(&ht, hash_string, hash_less, NULL);
  while(cnt++ < 10)
  {
    s = (struct my_s *)malloc(sizeof(struct my_s));
    if (!fgets(s->str, 20, stdin))
    {
      printf("Wrong!\n");
      return 0;
    }
    hash_insert(&ht, &s->hash_elem);
  }

  cnt = hash_buckets(&ht);

  while(--cnt >= 0)
  {
    printf("%d ", hash_each_size(&ht, cnt));
  }

  printf("\n");
}
