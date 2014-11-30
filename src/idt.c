#include "idt.h"
#include "stdfunc.h"

typedef struct idt_entry_s idt_entry_t;
typedef struct idt_ptr_s   idt_ptr_t;

idt_entry_t idt_entries[256];
idt_ptr_t   idtp;

extern void idt_load();

void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags)
{
	idt_entries[num].base_lo = base & 0xFFFF;
	idt_entries[num].base_hi = (base >> 16) & 0xFFFF;

	idt_entries[num].sel     = sel;
	idt_entries[num].always0 = 0;

	idt_entries[num].flags   = flags;
}

void InitializeIDT(void) 
{
	idtp.limit = sizeof(idt_entry_t) * 256 - 1;
	idtp.base  = (uint32_t)&idt_entries;

	memset(&idt_entries, 0, sizeof(idt_entry_t) * 256);

	idt_set_gate(1, (uint32_t)isr0, 0x08, 0x8E);
	idt_set_gate(2, (uint32_t)isr0, 0x08, 0x8E);
	idt_set_gate(3, (uint32_t)isr0, 0x08, 0x8E);
	idt_set_gate(4, (uint32_t)isr0, 0x08, 0x8E);
	idt_set_gate(5, (uint32_t)isr0, 0x08, 0x8E);
	idt_set_gate(6, (uint32_t)isr0, 0x08, 0x8E);
	idt_set_gate(7, (uint32_t)isr0, 0x08, 0x8E);
	idt_set_gate(8, (uint32_t)isr0, 0x08, 0x8E);
	idt_set_gate(9, (uint32_t)isr0, 0x08, 0x8E);
	idt_set_gate(10, (uint32_t)isr0, 0x08, 0x8E);
	idt_set_gate(11, (uint32_t)isr0, 0x08, 0x8E);
	idt_set_gate(12, (uint32_t)isr0, 0x08, 0x8E);
	idt_set_gate(13, (uint32_t)isr0, 0x08, 0x8E);
	idt_set_gate(14, (uint32_t)isr0, 0x08, 0x8E);
	idt_set_gate(15, (uint32_t)isr0, 0x08, 0x8E);
	idt_set_gate(16, (uint32_t)isr0, 0x08, 0x8E);
	idt_set_gate(17, (uint32_t)isr0, 0x08, 0x8E);
	idt_set_gate(18, (uint32_t)isr0, 0x08, 0x8E);
	idt_set_gate(19, (uint32_t)isr0, 0x08, 0x8E);
	idt_set_gate(20, (uint32_t)isr0, 0x08, 0x8E);
	idt_set_gate(21, (uint32_t)isr0, 0x08, 0x8E);
	idt_set_gate(22, (uint32_t)isr0, 0x08, 0x8E);
	idt_set_gate(23, (uint32_t)isr0, 0x08, 0x8E);
	idt_set_gate(24, (uint32_t)isr0, 0x08, 0x8E);
	idt_set_gate(25, (uint32_t)isr0, 0x08, 0x8E);
	idt_set_gate(26, (uint32_t)isr0, 0x08, 0x8E);
	idt_set_gate(27, (uint32_t)isr0, 0x08, 0x8E);
	idt_set_gate(28, (uint32_t)isr0, 0x08, 0x8E);
	idt_set_gate(29, (uint32_t)isr0, 0x08, 0x8E);
	idt_set_gate(30, (uint32_t)isr0, 0x08, 0x8E);
	idt_set_gate(31, (uint32_t)isr0, 0x08, 0x8E);

	idt_flush((uint32_t)&idtp);
}
