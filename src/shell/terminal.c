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

//Generate color for terminal interface
uint8_t make_color(enum vga_color fg, enum vga_color bg) {
	return fg | bg << 4;
}

uint8_t make_color_s(size_t fg, size_t bg) {
    return fg | bg << 4;
}

//Create char suitable for writing to memory
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

//Intialize terminal
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

//Sets color of terminal
void terminal_setcolor(uint8_t color) {
	terminal_color = color;
}

//Displays one char at given location with given color
void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) {
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = make_vgaentry(c, color);
}

//Displays one char at given location
void terminal_putcharat(char c, size_t x, size_t y) {
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = make_vgaentry(c, terminal_color);
}

//Displays one char
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
		terminal_movecursor(terminal_column + 1, terminal_row);
        break;
    case '\b':
        if(terminal_column < 1)
        {
            terminal_row -= 1;
            terminal_column = -1;
        }
        else 
            terminal_column -= 2;

        terminal_movecursor(terminal_column + 1, terminal_row);
        terminal_putentryat(' ', terminal_color, terminal_column + 1, terminal_row);
        break;
    case '\t':
        terminal_column += 4;
        terminal_movecursor(terminal_column + 1, terminal_row);
        break;
    case '0':
        break;
    default:
        terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
		terminal_movecursor(terminal_column + 1, terminal_row);
        break;
	}
    
	if(terminal_column == VGA_WIDTH) 
	{
		terminal_column = 0;
        terminal_row++;
		
	}

    if(terminal_row == VGA_HEIGHT)
    {
        terminal_movescreen();
    }

    terminal_column++;
}

//Writes a string to display 
void terminal_writestring(const char* data) {
	size_t datalen = strlen(data);
	for(size_t i = 0; i < datalen; i++) {
		terminal_putchar(data[i]);
	}
}

//Moves cursor to [x, y] position
void terminal_movecursor(size_t x, size_t y)
{
	size_t index;

	index = y * 80 + x;

	outportb(0x3D4, 14);
	outportb(0x3D5, index >> 8);
	outportb(0x3D4, 15);
	outportb(0x3D5, index);
}

//Moves screen one line down
void terminal_movescreen()
{

   for(size_t i = 0; i < VGA_WIDTH * (VGA_HEIGHT - 1); i++) {

       terminal_buffer[i] = terminal_buffer[i + VGA_WIDTH];

   }

   terminal_row--;
   terminal_column = 0;

   for(size_t i = 0; i < VGA_WIDTH; i++) {
       terminal_buffer[VGA_WIDTH * (VGA_HEIGHT - 1) + i] = make_vgaentry(' ', terminal_color);
   }

   terminal_movecursor(terminal_column--, terminal_row);

}

//Clears display
void terminal_clearscreen() 
{
	for(size_t y = 0; y < VGA_HEIGHT; y++) {
		for(size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = make_vgaentry(' ', terminal_color);
		}
	}

    terminal_row = 0;
    terminal_column = 1;

	terminal_movecursor(terminal_row, terminal_column--);
}

//Saves terminal line into suplied buffer
char* terminal_getline(size_t line, char* buf)
{

    for(size_t x = 0; x < VGA_WIDTH; x++)
    {
        
        buf[x] = terminal_getcharat(x, line);

    }

    buf[VGA_WIDTH] = '\0';

    return &buf[0];

}

//Gets character at given location
char terminal_getcharat(size_t x, size_t y)
{

    uint8_t character = terminal_buffer[y * VGA_WIDTH + x];

    return character;
}
