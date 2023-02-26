all:
	make -C stage1
	make -C stage2
	make -C kernel
	i686-elf-ld -o bin/bootloader.bin -Ttext 0x1000 bin/stage2_entry.o bin/stage2.o bin/stdio.o bin/gdt.o bin/memory.o bin/fat.o bin/ports.o --oformat binary
	i686-elf-ld -o bin/kernel.bin -Ttext 0x1000 bin/kernel.o --oformat binary
	cat bin/stage1.bin bin/bootloader.bin > bin/galaxy.bin
	dd if=/dev/zero of=bin/galaxy.img bs=512 count=2880 >/dev/null
	mkfs.fat -F 12 -n "GALAXY" bin/galaxy.img >/dev/null
	mmd -i bin/galaxy.img ::/test >/dev/null
	# mcopy -i bin/galaxy.img assets/text.txt ::/test >/dev/null
	dd if=bin/galaxy.bin of=bin/galaxy.img conv=notrunc >/dev/null
	dd if=bin/kernel.bin of=bin/galaxy.img bs=512 count=5 seek=19 conv=notrunc >/dev/null

run:
	qemu-system-i386 -m 512M -fda bin/galaxy.img

clean:
	rm -f bin/*
