#include "../include/list.h"
#include "../include/debug.h"

/* initialize a list */
void *list_init(struct list *list_) 
{
  ASSERT(list_ != NULL);
  list_->head.next = &list_->tail;
  list_->head.prev = NULL;
  list_->tail.prev = &list_->head;
  list_->tail.next = NULL;
  printf("list initialized\n");
}
