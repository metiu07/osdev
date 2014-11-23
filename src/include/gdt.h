struct gdt_ptr_s
{
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));
