CC=gcc
CFLAGS=-m32 -ffreestanding -fno-pie -fno-pic -nostdlib
OUTPUT=../bin/kernel.bin

all:
	i686-elf-gcc -ffreestanding -m32 -g -c kernel.c -o ../bin/kernel.o -lgcc