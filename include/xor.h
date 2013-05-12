#ifndef __XOR_LIST_H
#define __XOR_LIST_H
#include <stdint.h>
#include <stddef.h>
#include <assert.h>
#include <stdbool.h>

struct xor_list_elem
{
  struct xor_list_elem *xor_addr;
};

struct xor_list
{
  struct xor_list_elem head;
  struct xor_list_elem tail;
};

/* define offsetof: find the offset of the member in *
 * type( here is our own predefined structure )      */
#ifndef NULL
#define NULL ((void *) 0)
#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *) 0)->MEMBER)
#endif

/* use the address of XOR_ADDR subtract the offset of *
 * XOR_ADDR in STRUCT                                 */
#define xor_list_entry(XOR_LIST_ELEM, STRUCT, MEMBER)                    \
        ((STRUCT *) ((uint8_t *) &(XOR_LIST_ELEM)->xor_addr          \
                                - offsetof(STRUCT, MEMBER.xor_addr)))

typedef bool xor_list_compare_func(const struct xor_list_elem *a,
                                   const struct xor_list_elem *b); /* comparesion function */

/* xor list init */
void xor_list_init(struct xor_list *xl);
bool xor_list_empty(struct xor_list *xl);

/* xor list node information */
struct xor_list_elem *xor_list_begin(struct xor_list *xl);
struct xor_list_elem *xor_list_head(struct xor_list *xl);
struct xor_list_elem *xor_list_tail(struct xor_list *xl);
struct xor_list_elem *xor_list_last(struct xor_list *xl);

/* xor list traverse operation */
struct xor_list_elem *xor_list_next(struct xor_list_elem *pre,
                                    struct xor_list_elem *cur,
                                    struct xor_list *xl);          //next
struct xor_list_elem *xor_list_prev(struct xor_list_elem *pre,
                                    struct xor_list_elem *after,
                                    struct xor_list *xl);        //prev

/* xor list insertion */
void xor_list_push_front(struct xor_list *xl, struct xor_list_elem *new);
void xor_list_push_back(struct xor_list *xl, struct xor_list_elem *new);
void xor_list_insert(struct xor_list_elem *pre,
                     struct xor_list_elem *next,
                     struct xor_list_elem *new, 
                     struct xor_list *xl);          //insert

/* xor list remove opertion */
struct xor_list_elem *xor_list_popfront(struct xor_list *xl);
struct xor_list_elem *xor_list_popback(struct xor_list *xl);
struct xor_list_elem *xor_list_remove(struct xor_list_elem *before,
                                      struct xor_list_elem *after,
                                      struct xor_list_elem *d,
                                      struct xor_list *xl);
struct xor_list_elem *xor_list_delete_element(struct xor_list_elem *del,
                                              struct xor_list *xl,
                                              xor_list_compare_func cmp_func);

/* xor list search operation */

struct xor_list_elem *xor_list_find(struct xor_list *xl,
                                    struct xor_list_elem *target,
                                    xor_list_compare_func cmp_func);
static struct xor_list_elem *prev, *tmp;

#define for_each_xor_element(xl, e)  for(prev = xor_list_head(xl),       \
                                         e = xor_list_begin(xl);         \
                               e != xor_list_tail(xl) && (tmp = e);      \
                               e = xor_list_next(prev, e, xl), prev = tmp)

#define delete_each_xor_element(xl, e) for(prev = xor_list_head(xl),     \
                                   e = xor_list_begin(xl), tmp = e ;     \
                                   tmp != xor_list_tail(xl) && (e = tmp);\
                                   tmp = xor_list_next(prev, e, xl),     \
                                   e = xor_list_remove(prev, tmp, e, xl))
#endif
