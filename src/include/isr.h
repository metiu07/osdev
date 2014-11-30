#ifndef ISR_H
#define ISR_H

#include <stdint.h>

struct registers_t
{
	uint32_t ds;
	uint32_t edi, esi, edp, esp, ebx, edx, ecx, eax;
	uint32_t int_no, err_code;
	uint32_t eip, cs, eflags, useresp, ss;
};

#endif
