#include <stdbool.h>

#include "shell.h"
#include "common.h"
#include "terminal.h"
#include "keyboard.h"
#include "stdfunc.h"

char shell_buffer[SHELL_BUFFER_SIZE];
uint16_t shell_buffersize = 0;
bool running = false;

void shell_bufferclear()
{
    shell_buffersize = 0;
}

void shell_bufferpush(char c)
{
    if(shell_buffersize < SHELL_BUFFER_SIZE)
    {
        shell_buffer[shell_buffersize] = c;
        shell_buffersize++;
    }
}

char shell_bufferpop()
{
    if(shell_buffersize)
    {
        shell_buffersize--;
        return shell_buffer[shell_buffersize];
    }

    return 0;
}

char* shell_bufferread()
{
    shell_bufferpush('\0');
    return shell_buffer;
}

void shell_clear()
{
    terminal_writestring("mato:myos/$ ");
    shell_bufferclear();
}

void shell_exit()
{
    shell_bufferclear();
    terminal_clearscreen();
}

void shell_command_help(int argc, char *argv[])
{
    terminal_writestring("Syntax: help <prikaz>\n");
    terminal_writestring("clear -> Vycisti obrazovku\n");
}

void shell_command_clear()
{
    terminal_clearscreen();
    shell_bufferclear();
}

void shell_command_color(int argc, char *argv[])
{
    if (argc == 2) {
        uint8_t fg = atoi(argv[1]);
        uint8_t bg = atoi(argv[2]);
        terminal_setcolor(make_color_s(fg, bg));
    } else {
        terminal_writestring("Zadal si nepravny pocet argumentov: ");
        terminal_writestring(itoa(argc, 10));
        terminal_putchar('\n');
    }
}

void shell_command_test(int argc, char *argv[])
{
    terminal_writestring("Test message!\n");
    terminal_writestring(argv[0]);
    terminal_putchar('\n');
}

void shell_command_exit()
{
    running = false;
    terminal_writestring("[+]Exiting...");
}

void shell_interpreter(char *command)
{
    int argc = 0;
    char argv[32][32];
    int start = 0;
    int current = 0;
    int i;
    int j = 0;

    while(command[current] != '\0')
    {
        if(command[current] == ' ' || command[current] == '\n')
        {
            j = 0;
            for(i = start; i < current; i++)
            {
                argv[argc][j] = command[i];
                j++;
            }

            argv[argc][j] = '\0';
            argc++;

            start = current + 1;

        }

        current++;
    }

    argc--;

    if(strcmp(argv[0], "test") == 0)
    {
        shell_command_test(argc, argv);
    }
    else if (strcmp(argv[0], "help") == 0)
    {
        shell_command_help(argc, argv);
    }
    else if (strcmp(argv[0], "color") == 0)
    {
        shell_command_color(argc, argv);
    }
    else if (strcmp(argv[0], "clear") == 0)
    {
        shell_command_clear();
    }
    else if (strcmp(argv[0], "exit") == 0)
    {
        shell_command_exit();
    }
    else if (strcmp(argv[0], "") == 0)
    {
        //Do nothing
    }
    else
    {
        terminal_writestring(argv[0]);
        terminal_writestring(": Prikaz nebol najdeny\n");
    }

    shell_clear();
}

void InitializeShell()
{
    terminal_writestring("MatoOS\n");
    terminal_writestring("Pre pomoc pouzi prikaz help\n");

    shell_clear();

    running = true;

    while(running)
    {
        char c;

        if((c = getchar()))
        {
            if(c == '\b')
            {
                if(shell_bufferpop())
                {
                    terminal_putchar('\b');
                }
            }
            else 
            {
                shell_bufferpush(c);
                terminal_putchar(c);
            }

            if(c == '\n')
            {
                shell_interpreter(shell_bufferread());
            }    
        }
    }

    shell_exit();
}
