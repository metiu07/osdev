#include "isr.h"
#include "terminal.h"
#include "common.h"

void isr_handler(struct registers_t regs)
{
	//do some writing
	terminal_writestring("Interupt HURAAA!");	

 	char* slovo = 0;
	slovo =	atoi(regs.int_no, slovo, 10);

	terminal_writestring(slovo);

	for(;;);

}
