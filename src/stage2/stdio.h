#pragma once
#include <stdint.h>

int strlen(char *s);
void putcar(unsigned char c);
void itoa(char *buf, unsigned long int n, int base);
void printk(char *s, ...);