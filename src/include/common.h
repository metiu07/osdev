#ifndef COMMON_H
#define COMMON_H

char* atoi(int value, char* str, int base);
char* itoa(int value, int base);
unsigned char inportb(unsigned short port);
void outportb(unsigned short port, unsigned char data);

#endif
