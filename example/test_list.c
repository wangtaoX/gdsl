#include "../include/list.h"
#include <stdio.h>

struct my_struct 
{
  struct list_elem le;
  int num;
};

int main()
{
  struct list my_list;
  struct my_struct ms;
  struct list_elem *le;
  struct my_struct *pms;

  ms.num = 10;

  list_init(&my_list);
  list_push_front(&my_list, &ms.le);

  le = list_begin(&my_list);
  pms = list_entry(le, struct my_struct, le);
  printf("%d\n", pms->num);
}
