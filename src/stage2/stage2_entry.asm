section .text
	[bits 32]
	[extern stage2_entry]
	call stage2_entry
	jmp $