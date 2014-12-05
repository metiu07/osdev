#include "keyboard.h"
#include "common.h"
#include "terminal.h"
#include "isr.h"
#include <stdbool.h>

const uint8_t usascii_kbd[128] = 
{
	// First row of keys on the keyboard
	0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
	// Second row of keys
	'\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
	// Third row of keys
	0 /* ctrl */, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0, /* lshift */
	// Forth row of keys
	'\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, /* rshift */
	'*',
	0,   // Alt
	' ', // space
	0,   // caps lock
	// f1 - f10 keys
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0,   // num lock
	0,   // scroll lock
	0,   // home key
	0,   // arrow key - Up
	0,   // page up
	'-', // dash key
	0,   // arrow key - left
	0,   // ?
	0,   // arrow key - right
	'+', // plus key
	0,   // end key
	0,   // arrow key - down
	0,   // page down
	0,   // insert key
	0,   // delete key
	// ?
	0, 0, 0,
	0,   // F11 key
	0,   // F12 key
	0,   // anything else is undefined.
};

const uint8_t usascii_kbd_shift[128] = 
{
	// First row of keys on the keyboard
	0, 27, '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '\b',
	// Second row of keys
	'\t', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n',
	// Third row of keys
	0 /* ctrl */, 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '"', '~', 0, /* lshift */
	// Forth row of keys
	'|', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?', 0, /* rshift */
	'*',
	0,   // Alt
	' ', // space
	0,   // caps lock
	// f1 - f10 keys
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0,   // num lock
	0,   // scroll lock
	0,   // home key
	0,   // arrow key - Up
	0,   // page up
	'-', // dash key
	0,   // arrow key - left
	0,   // ?
	0,   // arrow key - right
	'+', // plus key
	0,   // end key
	0,   // arrow key - down
	0,   // page down
	0,   // insert key
	0,   // delete key
	// ?
	0, 0, 0,
	0,   // F11 key
	0,   // F12 key
	0,   // anything else is undefined.
};

bool shift = false;
bool caps = false;

void keyboard_handler(struct registers_t regs) 
{
	uint8_t scancode = inportb(0x60);

	if (scancode & 0x80)
	{
		if (scancode == 0xAA || scancode == 0xB6)
			shift = false;
	}
	else
	{
		if (scancode == 0x2A || scancode == 0x36)
			shift = true;
		
		if (scancode == 0x3A)
			caps = !caps;

		if (shift)
		{
			
			if (caps)
				terminal_putchar(usascii_kbd[scancode]);
			else 
				terminal_putchar(usascii_kbd_shift[scancode]);
		}
		else
		{
			if (caps)
				terminal_putchar(usascii_kbd_shift[scancode]);
			else
				terminal_putchar(usascii_kbd[scancode]);
		}
	}
}

void InitializeKeyboard()
{
	register_interupt_handler(33, &keyboard_handler);	
}
