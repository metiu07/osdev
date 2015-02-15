#include "common.h"

char* atoi(int value, char * str, int base)
{

	char* rc;
	char* ptr;
	char* low;

	if ( base < 2 || base > 36)
	{
		*str = '\0';
		return str;
	}

	rc = ptr = str;

	if( value < 0 && base == 10)
	{
		*ptr++ = '-';
	}

	low = ptr;

	do
	{
		*ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz"[35 + value % base];
		value /= base;
	} while(value);

	*ptr-- = '\0';

	while(low < ptr)
	{
		char tmp = *low;
		*low++ = *ptr;
		*ptr-- = tmp;
	}

	return rc;
}

unsigned char inportb(unsigned short port)
{
	unsigned char output;
	asm volatile ("inb %1, %0" : "=a" (output) : "dN" (port));
	return output;
}

void outportb(unsigned short port, unsigned char data)
{
	asm volatile("outb %1, %0" : : "dN" (port), "a" (data));
}
