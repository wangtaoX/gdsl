#include "../include/xor.h"

#define XOR(x, y) (((uintptr_t)(x) ^ (uintptr_t)(y)))

/* init the list */
void xor_list_init(struct xor_list *xl)
{
  assert(xl != NULL);

  xl->head.xor_addr = &xl->tail;
  xl->tail.xor_addr = &xl->head;
}

/* wether is a empty list */
bool xor_list_empty(struct xor_list *xl)
{
  assert(xl != NULL);

  return xor_list_tail(xl) == xor_list_begin(xl);
}

/* return the first element of its list, when the list
 * is empty, the return value point to the list tail*/
struct xor_list_elem * xor_list_begin(struct xor_list *xl)
{
  assert(xl != NULL); 
  return xl->head.xor_addr;
}

/* return the last element of its list, when the list
 * is empty, the return value point to the list head */
struct xor_list_elem *xor_list_last(struct xor_list *xl)
{
  assert(xl != NULL);
  return xl->tail.xor_addr;
}

/* return list head */
struct xor_list_elem * xor_list_head(struct xor_list *xl)
{
  assert(xl != NULL);
  return &xl->head;
}

/* return list tail */
struct xor_list_elem * xor_list_tail(struct xor_list *xl)
{
  assert(xl != NULL);
  return &xl->tail;
}

/* return the element after CUR in its list, if CUR is 
 * the last element or the first element, return the tail
 * of the list */
struct xor_list_elem *xor_list_next(struct xor_list_elem *pre,
                                    struct xor_list_elem *cur,
                                    struct xor_list *xl)
{

  if (cur == xor_list_head(xl) ||
      cur == xor_list_tail(xl))
    return xor_list_tail(xl);
  return (struct xor_list_elem *)XOR(pre, cur->xor_addr);
}

/* return the element before PRE, if PRE is the last
 * element or the first element, return the head of the list */
struct xor_list_elem *xor_list_prev(struct xor_list_elem *pre,
                                    struct xor_list_elem *after,
                                    struct xor_list *xl)
{
  if (pre == xor_list_head(xl) ||
      pre == xor_list_tail(xl))
    return xor_list_head(xl);
  return (struct xor_list_elem *)
    XOR(pre->xor_addr, after); // bug here, use pre->xor_addr 
                               // instead of pre
}

/* insert a new element after NEXT */
void xor_list_insert(struct xor_list_elem *pre,
                     struct xor_list_elem *next,
                     struct xor_list_elem *new,
                     struct xor_list *xl)
{
  struct xor_list_elem *__p, *__n, *__d;
  assert(pre != NULL && next != NULL);
  
  if (next == xor_list_tail(xl) 
      && pre  == xor_list_head(xl))
  {
    pre->xor_addr = new;
    next->xor_addr = new;
    new->xor_addr = (struct xor_list_elem *)
      XOR(pre, next);
   return; 
  }

  assert(next != xor_list_tail(xl));
  __n = (struct xor_list_elem *)XOR(pre, next->xor_addr);
  __p = next;
  __d = (struct xor_list_elem *)
    XOR(next, ((struct xor_list_elem *)__n)->xor_addr);

  next->xor_addr = (struct xor_list_elem *)(XOR(pre, new));
  new->xor_addr = (struct xor_list_elem *)(XOR(__n, __p));
  ((struct xor_list_elem *)__n)->xor_addr = (struct xor_list_elem *)XOR(__d, new);
}

/* insert the element NEW at the beginning of the list */
void xor_list_push_front(struct xor_list *xl,
                         struct xor_list_elem *new)
{
  struct xor_list_elem *__b, *__h, *__t = NULL;
  assert(new != NULL && xl != NULL);

  __b = xor_list_begin(xl);
  __h = xor_list_head(xl);
  if (__b != xor_list_tail(xl))
    __t = (struct xor_list_elem *)XOR(__h, __b->xor_addr); /* bug here!!! 
                                         use __b->xor_addr instead of __b */

  __h->xor_addr = new;
  new->xor_addr = (struct xor_list_elem *)XOR(__h, __b);
  if (__t == NULL)
    __b->xor_addr = new;
  else
    __b->xor_addr = (struct xor_list_elem *)XOR(__t, new);
}

/* insert element NEW at the end of the list */
void xor_list_push_back(struct xor_list *xl,
                        struct xor_list_elem *new)
{
  struct xor_list_elem *__h, *__t;
  assert(new != NULL && xl != NULL);
  if (xor_list_empty(xl))
  {
    __h = xor_list_head(xl);
    __t = xor_list_tail(xl);
    new->xor_addr = (struct xor_list_elem *)XOR(__h, __t);
    __h->xor_addr = new;
    __t->xor_addr = new;

    return;
  }

  xor_list_insert(xor_list_prev(xor_list_last(xl), xor_list_tail(xl), xl),
      xor_list_last(xl), new, xl);
}

/* remove the element d, which between the element    *
 * BEFORE and AFTER, and return the deleted element D */
struct xor_list_elem * 
xor_list_remove(struct xor_list_elem *before,
                struct xor_list_elem *after,
                struct xor_list_elem *d,
                struct xor_list *xl)
{
  struct xor_list_elem *e = before;

  assert(d != xor_list_head(xl) 
      && d != xor_list_tail(xl));

  before->xor_addr = (struct xor_list_elem *)
    XOR(XOR(d, before->xor_addr), after);
  after->xor_addr =  (struct xor_list_elem *)
    XOR(XOR(d, after->xor_addr), before);

  return d;
}

/* remove the first element */
struct xor_list_elem *
xor_list_popfront(struct xor_list *xl)
{
  struct xor_list_elem *__h, *__b;

  if (xor_list_empty(xl))
    return NULL;

  __h = xor_list_head(xl);
  __b = xor_list_begin(xl);
  return xor_list_remove(__h, 
      xor_list_next(__h, __b, xl), __b, xl);
}

/* remove thr last element */
struct xor_list_elem *
xor_list_popback(struct xor_list *xl)
{
  struct xor_list_elem *__t, *__l;

  if (xor_list_empty(xl))
    return;

  __t = xor_list_tail(xl);
  __l = xor_list_last(xl);

  return xor_list_remove(xor_list_prev(__l, __t, xl),
      __t, __l, xl);
}

/* find target in xor_list XL */
struct xor_list_elem *xor_list_find(struct xor_list *xl,
                                    struct xor_list_elem *target,
                                    xor_list_compare_func cmp_func)
{
  struct xor_list_elem *e;

  assert(target != NULL 
      && xl != NULL);

  if (xor_list_empty(xl))
    return NULL;

  for_each_xor_element(xl, e)
  {
    if (cmp_func(target, e))
      return e;
  }
  return NULL;
}

/* delete a given element */
struct xor_list_elem *xor_list_delete_element(struct xor_list_elem *del,
    struct xor_list *xl, xor_list_compare_func cmp_func)
{
  struct xor_list_elem *e;
  if (del == NULL ||
      xor_list_empty(xl))
    return del;

  for_each_xor_element(xl, e)
  {
    if (cmp_func(del, e))
      return xor_list_remove(prev, xor_list_next(prev, e, xl),
         e, xl);
  }

  return NULL;
}
