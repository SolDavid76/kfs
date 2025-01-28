bits 32

section .text
	global load_gdt
	global get_stack_pointer

	get_stack_pointer:
		mov eax, esp
		ret

	load_gdt:
		mov eax, [esp + 4]
		lgdt [eax]

		mov ax, 0x10
		mov ds, ax
		mov es, ax
		mov fs, ax
		mov ss, ax
	
		mov ax, 0x18
		mov gs, ax
	.flush:
		ret
