#include <stdint.h>
#include "kfs.h"

typedef struct s_GDTEntry
{
	uint16_t	limit_low; // Limite basse (16 bits)
	uint16_t	base_low; // Base basse (16 bits)
	uint8_t		base_mid; // Base moyenne (8 bits)
	uint8_t		access; // Attributs d'accès
	uint8_t		granularity; // Granularité et bits de limite élevée
	uint8_t		base_high; // Base haute (8 bits)
}				__attribute__((packed)) t_GDTEntry;

typedef struct s_GDT
{
	uint16_t	limit; // Taille de la GDT moins 1
	uint32_t	base; // Adresse de la GDT
}				__attribute__((packed)) t_GDT;

unsigned short	*terminal_buffer;
unsigned int 	vga_index;
__attribute__((aligned(16))) t_GDT							GDTPtr;
__attribute__((aligned(16), section(".gdt"))) t_GDTEntry	GDT[7];

extern load_gdt(void *);

void clear_screen(void)
{
	int index = 0;
	while (index < 80 * 25 * 2) {
		terminal_buffer[index] = ' ';
		index++;
	}
}

void print_char(char c, unsigned char color)
{
	terminal_buffer[vga_index] = (unsigned short)c | (unsigned short)color << 8;
	vga_index++;
}

void print_string(char* str, unsigned char color)
{
	int index = 0;
	while (str[index]) {
		terminal_buffer[vga_index] = (unsigned short)str[index] | (unsigned short)color << 8;
		index++;
		vga_index++;
	}
}

t_GDTEntry create_descriptor(uint32_t base, uint32_t limit, uint8_t access)
{
	t_GDTEntry descriptor;

	descriptor.limit_low = limit & 0xFFFF;
	descriptor.base_low = base & 0xFFFF;
	descriptor.base_mid = (base >> 16) & 0xFF;
	descriptor.access = access;
	descriptor.granularity = (limit >> 16) & 0x0F;
	descriptor.granularity |= 0xC0;
	descriptor.base_high = (base >> 24) & 0xFF;
	return (descriptor);
}


void init_GDT(void)
{
	GDTPtr.limit = sizeof(GDT) - 1;
	GDTPtr.base = (uint32_t)GDT;

	GDT[0] = (t_GDTEntry){0}; // NULL descriptor
	GDT[1] = create_descriptor(0, 0xFFFFF, 0x9A); // Kernel code
	GDT[2] = create_descriptor(0, 0xFFFFF, 0x92); // Kernel data
	GDT[3] = create_descriptor(0, 0xFFFFF, 0x92); // Kernel stack
	GDT[4] = create_descriptor(0, 0xFFFFF, 0xFA); // User code
	GDT[5] = create_descriptor(0, 0xFFFFF, 0xF2); // User data
	GDT[6] = create_descriptor(0, 0xFFFFF, 0xF2); // User stack

	load_gdt(&GDTPtr);
}

void printk(void)
{
	ft_putnbr_base(GDTPtr.base, "0123456789ABCDEF");
}

void main(void)
{
	terminal_buffer = (unsigned short*)VGA_ADDRESS;
	vga_index = 0;
	clear_screen();
	init_GDT();
	printk();
	return;
}
