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
	lgdt [gdt_desc]
	jmp 0x08:fix_cs

fix_cs:
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	mov esp, STACK_SPACE
	call kernel_main
	jmp $
	
gdt:
	gdt_null:
		dq 0
	gdt_code:
		dw 0xffff
		dw 0x0000
		db 0x00
		db 0x9a
		db 0xcf
		db 0x00
		
	gdt_data:
		dw 0xffff
		dw 0x0000
		db 0x00
		db 0x92
		db 0xcf
		db 0x00
		
	gdt_desc:
		dw gdt_desc - gdt - 1
		dd gdt
	
section .bss
	resb 2*1024*1024
	STACK_SPACE:
	
	
	
	
	
	
