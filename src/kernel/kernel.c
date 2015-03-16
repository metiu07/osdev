#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "gdt.h"
#include "idt.h"
#include "keyboard.h"
#include "terminal.h"
#include "stdfunc.h"
#include "common.h"
#include "timer.h"

#if defined(__linux__)
#error "Na skompilovanie nebol pouzity cross-compiler."
#endif

#if !defined(__i386__)
#error "Kernel musi byt skompilovany cross-compilerom."
#endif

void kernel_main() 
{
	terminal_initialize();
	terminal_writestring("HELLO WORLD!\n");

	terminal_writestring("[+]Inicialization of GDT\n");
    InitializeGDT();

	terminal_writestring("[+]Inicialization of IDT\n");
	InitializeIDT();

    terminal_writestring("[+]Inicialization of timer\n");
    InitializeTimer(50);

	terminal_writestring("[+]Inicialization of Keyboard\n");
	InitializeKeyboard();

    terminal_putentryat("\n\n");
    terminal_puchar(getCharAt(0, 0));

	while(true)
	{
		
	}

}
