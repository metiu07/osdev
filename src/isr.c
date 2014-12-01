#include "isr.h"
#include "terminal.h"

void isr_handler(struct registers_t regs)
{
	//do some writing
	terminal_writestring("Interupt HURAAA!");	
}
