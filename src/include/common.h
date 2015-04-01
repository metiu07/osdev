#ifndef COMMON_H
#define COMMON_H

int atoi(char* s);
char* itoa(int value, int base);
unsigned char inportb(unsigned short port);
void outportb(unsigned short port, unsigned char data);

#endif
