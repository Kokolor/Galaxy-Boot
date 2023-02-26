CC=gcc
CFLAGS=-m32 -ffreestanding -fno-pie -fno-pic -nostdlib -O0
OUTPUT=../bin/stage2.bin

all:
	i686-elf-gcc -ffreestanding -m32 -g -c stage2.c -o ../bin/stage2.o -lgcc
	i686-elf-gcc -ffreestanding -m32 -g -c fat.c -o ../bin/fat.o -lgcc
	i686-elf-gcc -ffreestanding -m32 -g -c ports.c -o ../bin/ports.o -lgcc
	i686-elf-gcc -ffreestanding -m32 -g -c memory.c -o ../bin/memory.o -lgcc
	i686-elf-gcc -ffreestanding -m32 -g -c stdio.c -o ../bin/stdio.o -lgcc
	i686-elf-gcc -ffreestanding -m32 -g -c gdt.c -o ../bin/gdt.o -lgcc
	nasm -f elf32 stage2_entry.asm -o ../bin/stage2_entry.o