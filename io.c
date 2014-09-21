#include "io.h"

inline unsigned char inportb(unsigned int port) {
	unsigned char ret;

	asm volatile ("inb %%dx,%%al;outb %%al,$0x80":"=a" (ret),"d" (port));
	return ret;
}

inline void outportb(unsigned int port, unsigned char value) 
{
	asm volatile ("outb %%al,%%dx;outb %%al,$0x80": :"d" (port), "a" (value));
}
