#include <stddef.h>

void *memcpy(void *dest, void const *src, size_t n)
{
	char *dp = dest;
	const char *sp = src;
	while(n--)
		*dp++ = *sp++;
	return dest;
}

void *memset(void *s, int c, size_t n)
{
	unsigned char* p = s;
	while(n--)
		*p++ = (unsigned char)c;
	return s;
}

size_t strlen(const char *s)
{
	const char *p = s;
	while(*s) ++s;
	return s - p;
}

