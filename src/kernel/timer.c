#include "timer.h"
#include "terminal.h"
#include "common.h"
#include "isr.h"

uint32_t tick = 0;

static void timer_tick() {
    tick++;
    terminal_writestring("Tick je: ");
    terminal_writestring("\n");
}

void InitializeTimer(uint32_t freq) {

    register_interupt_handler(IRQ0, &timer_tick);

    uint32_t delitel = 1193180 / freq;

    outportb(0x43, 0x36);

    uint8_t l = (uint8_t) (delitel & 0xFF);
    uint8_t h = (uint8_t) ((delitel >> 8) & 0xFF);

    outportb(0x40, l);
    outportb(0x40, h);
}
