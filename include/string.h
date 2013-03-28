#ifndef __STRING_H
#define __STRING_H

#include <stddef.h>

void *memscpy(void *dst, const void *src, size_t size);
void *memmove(void *dst, const void *src, size_t size);
int memcmp(const void *s1, const void *s2, size_t size);
#endif
