#include <stdint.h>

struct gdt_entry
{
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_middle;
    uint8_t access;
    uint8_t granularity;
    uint8_t base_high;
} __attribute__((packed));

struct gdt_pointer
{
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

struct gdt_entry gdt[3];
struct gdt_pointer gdtp;

void init_gdt(void)
{
    // Set up null segment descriptor
    gdt[0].limit_low = 0;
    gdt[0].base_low = 0;
    gdt[0].base_middle = 0;
    gdt[0].access = 0;
    gdt[0].granularity = 0;
    gdt[0].base_high = 0;

    // Set up code segment descriptor
    gdt[1].limit_low = 0xFFFF;
    gdt[1].base_low = 0;
    gdt[1].base_middle = 0;
    gdt[1].access = 0b10011010;
    gdt[1].granularity = 0b00100000;
    gdt[1].base_high = 0;

    // Set up data segment descriptor
    gdt[2].limit_low = 0xFFFF;
    gdt[2].base_low = 0;
    gdt[2].base_middle = 0;
    gdt[2].access = 0b10010010;
    gdt[2].granularity = 0b00000000;
    gdt[2].base_high = 0;

    // Load GDT
    gdtp.limit = sizeof(gdt) - 1;
    gdtp.base = (uint32_t)&gdt;

    asm volatile("lgdt %0"
                 :
                 : "m"(gdtp));
}