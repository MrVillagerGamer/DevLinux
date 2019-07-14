MAGIC equ 0x1BADB002
FLAGS equ (1<<0)|(1<<1)
CHECKSUM equ -(MAGIC + FLAGS)

section .multiboot
	dd MAGIC
	dd FLAGS
	dd CHECKSUM
	
section .text
	global _start
	extern kernel_main
_start:
	mov esp, STACK_SPACE
	push ebx
	call kernel_main
	jmp $

section .bss
	resb 2*1024*1024
	STACK_SPACE:
	
	
	
	
	
	
