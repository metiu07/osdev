#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "gdt.h"
#include "idt.h"
#include "terminal.h"
#include "stdfunc.h"

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

	asm volatile("int $0x10");

}
