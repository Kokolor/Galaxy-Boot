#include <stdint.h>

void outb(uint16_t port, uint8_t value)
{
    __asm__ volatile("outb %0, %1"
                     :
                     : "a"(value), "Nd"(port));
}

unsigned char inb(unsigned short port)
{
    unsigned char value;
    __asm__ __volatile__("inb %1, %0"
                         : "=a"(value)
                         : "Nd"(port));
    return value;
}

void insw(uint16_t port, void *buffer, uint32_t size)
{
    asm volatile("cld; rep insw"
                 : "+D"(buffer), "+c"(size)
                 : "d"(port)
                 : "memory");
}

int strcmp(const char *str1, const char *str2)
{
    while (*str1 && (*str1 == *str2))
    {
        str1++;
        str2++;
    }
    return *(const unsigned char *)str1 - *(const unsigned char *)str2;
}

void insl(uint32_t port, void* addr, uint32_t cnt) {
    asm volatile("cld; rep insl" : "+D" (addr), "+c" (cnt) : "d" (port) : "memory");
}
