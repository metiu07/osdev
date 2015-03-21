#include "isr.h"
#include "terminal.h"
#include "common.h"

isr_t interrupt_handlers[256];

void isr_handler(struct registers_t regs)
{
	terminal_writestring("[-]Interupt: ");	

	terminal_writestring(itoa(regs.int_no, 10));

    terminal_writestring("\n");
}

void irq_handler(struct registers_t regs)
{

	if(regs.int_no >= 40)
	{
		outportb(0xA0, 0x20);
	}

	outportb(0x20, 0x20);

	if(interrupt_handlers[regs.int_no] != 0)
	{
		isr_t handler = interrupt_handlers[regs.int_no];
		handler(regs);
	}
}

void register_interupt_handler(uint8_t n, isr_t handler)
{
	interrupt_handlers[n] = handler;
}
