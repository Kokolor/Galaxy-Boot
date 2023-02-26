[org 0x7c00]
stage2_adress equ 0x1000

mov [boot_disk], dl

xor ax, ax
mov es, ax
mov ds, ax
mov bp, 0x8000
mov sp, bp

mov bx, stage2_adress
mov dh, 50

mov ah, 0x02
mov al, dh
mov ch, 0x00
mov dh, 0x00
mov cl, 0x02
mov dl, [boot_disk]
int 0x13

mov ah, 0x0
mov al, 0x3
int 0x10

code_segement equ gdt_code - gdt_start
data_segement equ gdt_data - gdt_start

cli
lgdt [gdt_descriptor]
mov eax, cr0
or eax, 1
mov cr0, eax
jmp code_segement:start_protected_mode

jmp $

boot_disk: db 0

gdt_start:
	gdt_null:
		dd 0x0
		dd 0x0
	gdt_code:
		dw 0xffff
		dw 0x0
		db 0x0
		db 0b10011010
		db 0b11001111
		db 0x0
	gdt_data:
		dw 0xffff
		dw 0x0
		db 0x0
		db 0b10010010
		db 0b11001111
		db 0x0
gdt_end:
gdt_descriptor:
	dw gdt_end - gdt_start - 1
	dd gdt_start

[bits 32]
start_protected_mode:
	mov ax, data_segement
	mov ds, ax
	mov ss, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ebp, 0x90000
	mov esp, ebp
	jmp stage2_adress

times 510-($-$$) db 0
dw 0xaa55