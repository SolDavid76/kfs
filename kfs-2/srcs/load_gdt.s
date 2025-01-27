bits 32

section .text
	global load_gdt
	extern GDT


	load_gdt:
		lgdt [edi]

		mov ax, 0x10
		mov ds, ax
		mov es, ax
		mov fs, ax
		mov ss, ax

		mov ax, 0x18
		mov gs, ax
		jmp 0x8:.flush
	.flush:
		ret