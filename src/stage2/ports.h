#ifndef PORTS_H
#define PORTS_H

#include <stdint.h>

void outb(uint16_t port, uint8_t value);
unsigned char inb(unsigned short port);
void insw(uint16_t port, void *buffer, uint32_t size);
int strcmp(const char* str1, const char* str2);
void insl(uint32_t port, void* addr, uint32_t cnt);

#endif
