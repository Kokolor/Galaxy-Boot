#ifndef MEMORY_H
#define MEMORY_H

#include <stddef.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdbool.h>

void memory_init();
void *memmove(void *dest, const void *src, size_t n);
void *memcpy(char *dst, char *src, int n);
void *memset(void *ptr, int value, uint16_t num);
void *malloc(size_t size);
void free(void *p);

#endif