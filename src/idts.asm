IRQ_BASE equ 0x20
INTN dw 0

global load_idt
extern int_handle

%macro irq_entry_handler 1
global irq_entry_handler%1
irq_entry_handler%1:
	mov word [INTN], %1
	add word [INTN], IRQ_BASE
	pushad
	push word [INTN]
	push esp
	call int_handle
	pop esp
	pop word [INTN]
	popad
	iret
%endmacro

%macro int_entry_handler 1
global int_entry_handler%1
int_entry_handler%1:
	mov word [INTN], %1
	pushad
	push word [INTN]
	push esp
	call int_handle
	pop esp
	pop word [INTN]
	popad
	iret
%endmacro

irq_entry_handler 0
irq_entry_handler 1
irq_entry_handler 2
irq_entry_handler 3
irq_entry_handler 4
irq_entry_handler 5
irq_entry_handler 6
irq_entry_handler 7
irq_entry_handler 8
irq_entry_handler 9
irq_entry_handler 10
irq_entry_handler 11
irq_entry_handler 12
irq_entry_handler 13
irq_entry_handler 14
irq_entry_handler 15
	
load_idt:
	mov edx, [esp+4]
	lidt [edx]
	ret
	
	
	
	
	
	
	