#ifndef TERMINAL_H
#define TERMINAL_H

#include <stdint.h>
#include <stddef.h>

void terminal_initialize();
uint8_t make_color_s(size_t fg, size_t bg);
void terminal_setcolor(uint8_t color);
void terminal_putchar(char c);
void terminal_writestring(const char* data);
void terminal_putentryat(char c, uint8_t color, size_t x, size_t y);
void terminal_putcharat(char c, size_t x, size_t y);
void terminal_movecursor(size_t x, size_t y);
void terminal_movescreen();
void terminal_clearscreen();
char* terminal_getline(size_t line, char *buf);
char terminal_getcharat(size_t x, size_t y);

#endif
