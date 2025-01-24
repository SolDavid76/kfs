bits 32

section .text
	global load_gdt

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

	    jmp 0x08:reload  ; Changer de segment de code
	reload:
	    ret