#include <stddef.h>
#include "terminal.h" 
#include "common.h"
#include "stdfunc.h"

enum vga_color {
	COLOR_BLACK = 0,
	COLOR_BLUE = 1,
	COLOR_GREEN = 2,
	COLOR_CYAN = 3,
	COLOR_RED = 4,
	COLOR_MAGENTA = 5,
	COLOR_BROWN = 6,
	COLOR_LIGHT_GREY = 7,
	COLOR_DARK_GREY = 8,
	COLOR_LIGHT_BLUE = 9,
	COLOR_LIGHT_GREEN = 10,
	COLOR_LIGHT_CYAN = 11,
	COLOR_LIGHT_RED = 12,
	COLOR_LIGHT_MAGENTA = 13,
	COLOR_LIGHT_BROWN = 14,
	COLOR_WHITE = 15,
};

uint8_t make_color(enum vga_color fg, enum vga_color bg) {
	return fg | bg << 4;
}

uint16_t make_vgaentry(char c, uint8_t color) {
	uint16_t c16 = c;
	uint16_t color16 = color;
	return c16 | color16 << 8;
}

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;

void terminal_initialize() {
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = make_color(COLOR_LIGHT_GREY, COLOR_BLACK);
	terminal_buffer = (uint16_t*) 0xB8000;
	for(size_t y = 0; y < VGA_HEIGHT; y++) {
		for(size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = make_vgaentry(' ', terminal_color);
		}
	}
}

void terminal_setcolor(uint8_t color) {
	terminal_color = color;
}

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) {
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = make_vgaentry(c, color);
}

void terminal_putchar(char c) {

    if(c == 0)
    {
        return;
    }

    switch(c)
    {
    case '\n':
        terminal_row++;
		terminal_column = -1;
		terminal_moveCursor(terminal_column + 1, terminal_row);
        break;
    case '\b':
        if(terminal_column < 1)
        {
            terminal_row -= 1;
            terminal_column = -1;
        }
        else 
            terminal_column -= 2;

        terminal_moveCursor(terminal_column + 1, terminal_row);
        terminal_putentryat(' ', terminal_color, terminal_column + 1, terminal_row);
        break;
    case '\t':
        terminal_column += 3;
        terminal_moveCursor(terminal_column + 1, terminal_row);
    case '0':
        break;
    default:
        terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
		terminal_moveCursor(terminal_column + 1, terminal_row);
        break;
	}
    
	if(terminal_column + 1 == VGA_WIDTH) 
	{
		terminal_column = 0;
		if(terminal_row + 1 == VGA_HEIGHT)
		{
			terminal_row = 0;
			for(size_t y = 0; y <= VGA_HEIGHT; y++) 
				for(size_t x = 0; x <= VGA_WIDTH; x++) 
					terminal_buffer[y * VGA_WIDTH + x] = terminal_buffer[(y + 1) * VGA_WIDTH + x];
		}
	}

    terminal_column++;
}

void terminal_writestring(const char* data) {
	size_t datalen = strlen(data);
	for(size_t i = 0; i < datalen; i++) {
		terminal_putchar(data[i]);
	}
}

void terminal_moveCursor(size_t x, size_t y)
{
	size_t index;

	index = y * 80 + x;

	outportb(0x3D4, 14);
	outportb(0x3D5, index >> 8);
	outportb(0x3D4, 15);
	outportb(0x3D5, index);
}

void terminal_clearScreen() 
{
	for(size_t y = 0; y < VGA_HEIGHT; y++) {
		for(size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = make_vgaentry(' ', terminal_color);
		}
	}

	terminal_moveCursor(0, 0);
}
