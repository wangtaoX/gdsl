#ifndef __STRING_H
#define __STRING_H

#include <stddef.h>

void *memscpy(void *dst, const void *src, size_t size);
void *memmove(void *dst, const void *src, size_t size);
int memcmp(const void *s1, const void *s2, size_t size);
int strcmp(const char *s1, const char *s2);
void * memchr(const void *block, char c, size_t size);
char * strchr(const char *s1, char c);
size_t strlen(const char *s1);
size_t strlcpy(char *dst, const char *src, size_t size);
#endif
