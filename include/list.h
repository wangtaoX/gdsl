#ifndef __LIST_H
#define __LIST_H

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
/* A simple double linked list, eg: linux kernel list */

/* list element */
struct list_elem 
{
  struct list_elem *next;
  struct list_elem *prev;
};

/* list */
struct list 
{
  struct list_elem head;
  struct list_elem tail;
};

/* convert a list element pointer to a structure pointer, this
 * code is stolen from Linux kernel.
 * @LIST_ELEM: list element pointer 
 * @STRUCT: the structure name
 * @MEMBER: the name of the list element within the struct */
#define list_entry(LIST_ELEM, STRUCT, MEMBER) \
  (STRUCT *) ((uint8_t *) &(LIST_ELEM)->next \
      - offsetof(STRUCT, MEMBER.next))

/* list initialization
 * you can initialize your list like this:
 *      struct list my_list;
 *      list_init(&my_list);
 *
 * or you can initialize it like this:
 *      struct list my_list = LIST_INIT(my_list);
 */
#define LIST_INIT(NAME) {{&(NAME.tail), NULL},\
                         {NULL, &(NAME.head)}}
void list_init(struct list *list_);

/* list member */
struct list_elem *list_begin(struct list *list_);
struct list_elem *list_next(struct list_elem *list_elem_);
struct list_elem *list_end(struct list *list_);

struct list_elem *list_head(struct list *list_);
struct list_elem *list_tail(struct list *list_);

/* list operation */
int list_empty(struct list *list_);
int list_size(struct list *list_);

struct list_elem* list_remove(struct list_elem *old);

void list_push_front(struct list *list_, struct list_elem *new);
void list_push_back(struct list *list_, struct list_elem *new);
struct list_elem *list_pop_front(struct list *list_);
struct list_elem *list_pop_back(struct list *list_);
#endif
