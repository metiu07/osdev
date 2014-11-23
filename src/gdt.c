#include <stdint.h>
#include "gdt.h"

struct gdt_entry_s
{
	unsigned int limit_low:16;
	unsigned int base_low :24;
	unsigned int accessed :1;
	unsigned int read_write :1;
	unsigned int conforming_expand_down :1;
	unsigned int code :1;
    unsigned int always_1 :1;
    unsigned int DPL :2;
    unsigned int present :1;
    unsigned int limit_high :4;
    unsigned int available :1;
    unsigned int always_0 :1;
    unsigned int big :1;
    unsigned int gran :1;
    unsigned int base_high :8;
} __attribute__((packed));

typedef struct gdt_ptr_s gdt_ptr_t;
typedef struct gdt_entry_s gdt_entry_t;

extern void FlushGDT(uint32_t);

gdt_ptr_t   gdt_ptr;
gdt_entry_t gdt_entries[5];

void InitializeGDT(void)
{
    gdt_ptr.limit = (sizeof(gdt_entry_t) * 5) - 1;
    gdt_ptr.base  = (uint32_t)&gdt_entries;

    //memset(&gdt_entries[0], 0, sizeof(gdt_entry_t));

    gdt_entries[1].limit_low = 0x0000FFFF;
    gdt_entries[1].base_low = 0;
    gdt_entries[1].accessed = 0;
    gdt_entries[1].read_write = 1;
    gdt_entries[1].conforming_expand_down = 0;
    gdt_entries[1].code = 1;
    gdt_entries[1].always_1 = 1;
    gdt_entries[1].DPL = 0;
    gdt_entries[1].present = 1;
    gdt_entries[1].limit_high = 15;
    gdt_entries[1].available = 0;
    gdt_entries[1].always_0 = 0;
    gdt_entries[1].big = 1;
    gdt_entries[1].gran = 1;
    gdt_entries[1].base_high = 0;

    // Data segment
    gdt_entries[2].limit_low = 0x0000FFFF;
    gdt_entries[2].base_low = 0;
    gdt_entries[2].accessed = 0;
    gdt_entries[2].read_write = 1;
    gdt_entries[2].conforming_expand_down = 0;
    gdt_entries[2].code = 0;
    gdt_entries[2].always_1 = 1;
    gdt_entries[2].DPL = 0;
    gdt_entries[2].present = 1;
    gdt_entries[2].limit_high = 15;
    gdt_entries[2].available = 0;
    gdt_entries[2].always_0 = 0;
    gdt_entries[2].big = 1;
    gdt_entries[2].gran = 1;
    gdt_entries[2].base_high = 0;

    // User mode code segment
    gdt_entries[3].limit_low = 0x0000FFFF;
    gdt_entries[3].base_low = 0;
    gdt_entries[3].accessed = 0;
    gdt_entries[3].read_write = 1;
    gdt_entries[3].conforming_expand_down = 0;
    gdt_entries[3].code = 1;
    gdt_entries[3].always_1 = 1;
    gdt_entries[3].DPL = 3;
    gdt_entries[3].present = 1;
    gdt_entries[3].limit_high = 15;
    gdt_entries[3].available = 0;
    gdt_entries[3].always_0 = 0;
    gdt_entries[3].big = 1;
    gdt_entries[3].gran = 1;
    gdt_entries[3].base_high = 0;

    // User mode data segment
    gdt_entries[4].limit_low = 0x0000FFFF;
    gdt_entries[4].base_low = 0;
    gdt_entries[4].accessed = 0;
    gdt_entries[4].read_write = 1;
    gdt_entries[4].conforming_expand_down = 0;
    gdt_entries[4].code = 0;
    gdt_entries[4].always_1 = 1;
    gdt_entries[4].DPL = 3;
    gdt_entries[4].present = 1;
    gdt_entries[4].limit_high = 15;
    gdt_entries[4].available = 0;
    gdt_entries[4].always_0 = 0;
    gdt_entries[4].big = 1;
    gdt_entries[4].gran = 1;
    gdt_entries[4].base_high = 0;

    FlushGDT((uint32_t)&gdt_ptr);
}
