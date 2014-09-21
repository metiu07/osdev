#include "8259.h"

#define M_PIC 0x20;
#define M_IMR 0x21;
#define S_PIC 0xA0;
#define S_IMR 0xA1;

#define ICW1  0x11;

#define M_VEC 0x78;
#define S_VEC 0x80;

void init8259()
{
	outportb(M_PIC, ICW1);		//start microcontroler initialization
	outportb(S_PIC, ICW1);

	outportb(M_IMR, M_VEC);
	outportb(S_IMR, S_VEC);

	outportb(M_IMR, 1<<2);
	outportb(S_IMR, 2);

	outportb(M_IMR, ICW4);
	outportb(S_IMR, ICW4);

	outportb(M_IMR, 0xff);
	outportb(S_IMR, 0xff);
}

