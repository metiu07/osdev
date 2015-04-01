#include <stddef.h>

void* memcpy(void *dest, void *src, size_t n)
{
	char *dp = (char*)dest;
	char *sp = (char*)src;

	while(n--)
		*dp++ = *sp++;

	return dest;
}

void* memset(void *s, int c, size_t n)
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

int strcmp(const char* s1, const char* s2)
{
    while(*s1 && (*s1 == *s2))
        s1++,s2++;
    return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}
