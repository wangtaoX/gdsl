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

  list_init(&my_list);
  list_init(NULL);
}
