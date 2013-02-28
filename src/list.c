#include "../include/list.h"
#include "../include/debug.h"

/* initialize a list */
void list_init(struct list *list_) 
{
  ASSERT(list_ != NULL);
  list_->head.next = &list_->tail;
  list_->head.prev = NULL;
  list_->tail.prev = &list_->head;
  list_->tail.next = NULL;
  printf("list initialized\n");
}

/* return the first element in the list 
 * @list_ : the taeget list 
 */
struct list_elem *list_begin(struct list *list_)
{
  ASSERT(list_ != NULL);
  return list_->head.next;
}

/* return the last element in the list 
 *
 * Waring: if the list is empty, the result is equal to 
 * list_head()*/
struct list_elem *list_end(struct list *list_)
{
  ASSERT(list_ != NULL);

  return list_->tail.prev;
}

/* return the next element of the given element 
 * 
 * Waring : if the given element is tail of the 
 * its list, the behavior is undefined*/
struct list_elem *list_next(struct list_elem *list_elem_)
{
  ASSERT(list_elem_ != NULL);
  return list_elem_->next;
}

/* return the head of this list */
struct list_elem *list_head(struct list *list_)
{
  ASSERT(list_ != NULL);
  return &list_->head;
}

/* return the tail of this list */
struct list_elem *list_tail(struct list *list_)
{
  ASSERT(list_ != NULL);
  return &list_->tail;
}

/* return true if the list is empty */
int list_empty(struct list *list_)
{
  ASSERT(list_ != NULL);

  return list_end(list_) == list_head(list_);
}

/* return the number of element in list */
int list_size(struct list *list_)
{
  struct list_elem *le;
  struct list_elem *tail;
  int num = 0;
  ASSERT(list_ != NULL);

  tail = list_tail(list_);
  for (le = list_begin(list_); le != tail; le = list_next(le))
      num++;

  return num;
}

/* insert an element */
static void __list_insert(struct list_elem *prev, struct list_elem *next, struct list_elem *new)
{
  ASSERT(new != NULL);
  ASSERT(prev != NULL && next != NULL);

  next->prev = new;
  new->next = next;
  new->prev = prev;
  prev->next = new;
}

/* insert an element after the given list`s head */
void list_push_front(struct list *list_, struct list_elem *new)
{
  struct  list_elem *head;

  ASSERT(list_ != NULL && new != NULL);

  head = list_head(list_);
  return __list_insert(head, head->next, new);
}

static void __list_remove(struct list_elem *prev, struct list_elem *next)
{
  next->prev = prev;
  prev->next = next;
}
/* remove a given list element and return it */
struct list_elem *list_remove(struct list_elem *old)
{
  ASSERT(old != NULL);
  __list_remove(old->prev, old->next);

  return old;
}

/* insert an element before the given list`s tail */
void list_push_back(struct list *list_, struct list_elem *new)
{
  struct list_elem *tail;
  ASSERT(list_ != NULL);
  
  tail = list_tail(list_);
  return __list_insert(tail->prev, tail, new);
}

/* remove the first  element in the given list */
struct list_elem *list_pop_front(struct list *list_)
{
  struct list_elem *first;
  ASSERT(list_ != NULL && !list_empty(list_));

  first = list_begin(list_);
  __list_remove(first->prev, first->next);

  return first;
}

/* remove the last element in the given list */
struct list_elem *list_pop_back(struct list *list_)
{
  struct list_elem *last;
  ASSERT(list_ != NULL && !list_empty(list_));

  last = list_end(list_);
  __list_remove(last->prev, last->next);

  return last;
}
