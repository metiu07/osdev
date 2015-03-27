#include "common.h"

int atoi(char *s)
{
    int i,num=0,sign=1;

    for(i=0;s[i];i++)
        {
                if(s[i]==' ')
                        continue;
                else if(s[i]=='-') sign=-1;
                else break;
        }
        
        for(;s[i] && s[i]>='0' && s[i]<='9';i++)
                num=num*10 + s[i]-'0';
        return num*sign;
}

//Converts given integer to char
char* itoa(int value, int base)
{
    static char buf[32] = {0};

    int i = 30;
    
    for(; value && i; --i, value /= base)

        buf[i] = "0123456789abcdef"[value % base];

    return &buf[i + 1];

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
