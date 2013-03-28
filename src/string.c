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

  return dst;
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

/* Compare string s1 & s2 
 * Warning: s1 & s2 should not be NULL */

int strcmp(const char *s1, const char *s2)
{
  const unsigned char *s1_ = (const unsigned char *)s1;
  const unsigned char *s2_ = (const unsigned char *)s2;

  while( *s1_ != '\0' && *s1_ == *s2_)
  {
    s1_++;
    s2_++;
  }
  
  return *s1_ < *s2_ ? -1 : *s1 > *s2;
}

/* Return the pointer of the first occurrence of char C in BLOCK */

void * memchr(const void *block, char c, size_t size)
{
  const unsigned char *block_ = block;

  if (size <= 0 || block_ == NULL)
    return NULL;

  while (size-- > 0)
  {
    if (*block_++ == c)
      return (void *)block_;
  }

  return NULL;
}

/* Return the pointer of the first occurrence of char C in string S1 */
char * strchr(const char *s1, char c)
{
  const unsigned char *s1_ = (const unsigned char *)s1;

  if (s1 == NULL)
    return NULL;

  for(;;)
    if (*s1_ == c)
      return (char *)s1;
    else if (*s1_ == '\0')
      return NULL;
    else
      s1_++;
}

/* Return the length of string S1 */
size_t strlen(const char *s1)
{
  const char *s1_ = s1;

  if (s1 == NULL)
    return 0;

  for ( ;*s1_ != '\0'; s1_++)
     continue;
  return s1_ - s1;
}

/* Copy SRC to DST 
 * Waring: SRC & DST should not be NULL */
size_t strlcpy(char *dst, const char *src, size_t size)
{
  size_t src_len = strlen(src);
  size_t dst_len;

  if (size > 0)
  {
    dst_len = size - 1;
    if (src_len < dst_len)
      dst_len = src_len;
    memscpy(dst, src, dst_len);
    dst[dst_len] = '\0';
  }
  
  return src_len;
}
