bits 32

section .multiboot
	dd 0x1BADB002
	dd 0x0
	dd - (0x1BADB002 + 0x0)

section .text
	global start
	global load_gdt
	extern main


	load_gdt:
	    mov eax, [edi]
	    lgdt [eax]       ; Charger la GDT

	    ; Changer les segments
	    mov ax, 0x10     ; Kernel Data Segment (2ème entrée : offset 0x10)
	    mov ds, ax
	    mov es, ax
	    mov fs, ax
	    mov gs, ax

	    mov ax, 0x18     ; Kernel Stack Segment (3ème entrée : offset 0x18)
	    mov ss, ax

	    ret

	start:
		cli
		mov esp, stack_space
		call main
	hlt_loop:
		hlt
		jmp hlt_loop

section .bss
	resb 8192

stack_space:
