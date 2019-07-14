global gdt_flush
global gdt_load

gdt_init_user:
	cli
	push ax
	mov ax, 0x23
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ebp, esp
	push dword 0x23
	push eax
	pushfd
	push dword 0x1b
	push dword .cont
	iret
.cont:
	sti
	ret

gdt_flush:
	mov edx, [esp+4]
	lgdt [edx]
	jmp 0x08:.cont
.cont:
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	ret