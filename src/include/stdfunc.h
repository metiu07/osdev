#ifndef STDFUNC_H
#define STDFUNC_H

#include <stddef.h>

void *memcpy(void *dest, void const *src, size_t n);
void *memset(void *s, int c, size_t n);
size_t strlen(const char *s);

#endif
