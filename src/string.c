#include "../include/string.h"

/* Copy SIZE bytes from SRC to DST, return DST  *
 * Warning: No overlap here                     */
void *memscpy(void *dst, const void *src, size_t size)
{
  unsigned char *dst_ = dst;
  const unsigned char *src_ = src;

  if (size == 0 || dst_ == NULL ||src_ == NULL)
    return NULL;

  while(size-- > 0)
    *dst_++ = *src_++;

  return dst_;
}

/* Copy SIZE bytes from SRC to DST, return DST *
 * which allow overlap here                    */
void *memmove(void *dst, const void *src, size_t size)
{
  unsigned char * dst_ = dst;
  const unsigned char *src_ = src;

  if (size == 0 || dst_ == NULL || src_ == NULL)
    return NULL;

  /* DST is behind the SRC */
  if (dst_ > src_)
  {
    while (size-- > 0)
      *dst_++ = *src_++;
  } else /* The opposite case */
  {
    dst_ += size;
    src_ += size;

    while (size-- > 0)
      *--dst_ = *--src_;
  }

  return src_;
}

/* Compare two blocks of SIZE bytes 
 * Waring: S1 & S2 should not be NULL */
int memcmp(const void *s1, const void *s2, size_t size)
{
 const unsigned char *s1_ = s1;
 const unsigned char *s2_ = s2;

 for (; size-- > 0; s1_++, s2_++)
   if (*s1_ != *s2_)
     return *s1_ > *s2_ ? 1 : -1;

 return 0;
}
