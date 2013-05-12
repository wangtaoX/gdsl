#include "../include/xor.h"
#include <stdio.h>
#include <stdlib.h>


struct foo
{
  int i;
  struct xor_list_elem xle;
};

bool cmp_equal(const struct xor_list_elem *a,
    const struct xor_list_elem *b)
{
  struct foo *__a, *__b;

  __a = xor_list_entry(a, struct foo, xle);
  __b = xor_list_entry(b, struct foo, xle);

  return __a->i == __b->i;
}


int main()
{
  struct xor_list xl;
  int i;
  struct foo *f;
  struct xor_list_elem *c, *prev, *tmp;
  struct foo target;


  target.i = 2;
  xor_list_init(&xl);
  if(xor_list_empty(&xl))
    printf("empty xor list ;)\n");
  else
    printf("Error;(\n");
  for (i = 0; i<10; i++)
  {
    f = malloc(sizeof(struct foo));
    f->i = i;
    xor_list_push_back(&xl, &f->xle);
  }

  //prev = xor_list_head(&xl);
  //c = xor_list_begin(&xl);
  //while(c != xor_list_tail(&xl))
  //{
  //  tmp = c;
  //  f = list_entry(c, struct foo, xle);
  //  printf("%d ", f->i);
  //  c = xor_list_next(prev, c, &xl);
  //  prev = tmp;
  //}
  for_each_xor_element(&xl, c)
  {
    f = xor_list_entry(c, struct foo, xle);
    printf("%d ", f->i);
  }

  printf("\nafter\n");
  //for_each_xor_element(&xl, c)
  //{
  //  f = list_entry(c, struct foo, xle);
  //  printf("%d ", f->i);
  //}
  //while((c = xor_list_popfront(&xl)) != NULL)
  //{
  //  f = list_entry(c, struct foo, xle);
  //  printf("%d ", f->i);
  //}
  //printf("\n");
  //delete_each_xor_element(&xl, c)
  //{
  //  f = xor_list_entry(c, struct foo, xle);
  //  printf("%d ", f->i);
  //}
  c = xor_list_find(&xl, &(target.xle), cmp_equal);
  if (c != NULL)
  {
    f = xor_list_entry(c, struct foo, xle);
    printf("c %d\n", f->i);
  }
  if(xor_list_empty(&xl))
    printf("empty xor list ;)\n");
  else
    printf("Error;(\n");
}
