#include "kfs.h"

extern int load_gdt(void *);

unsigned short	*terminal_buffer = (unsigned short*)VGA_ADDRESS;
unsigned int 	vga_index = 0;
t_GDT			*GDTPtr = (t_GDT *)GDT_ADDRESS;
t_GDTEntry		GDT[7];

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
	GDTPtr->limit = (sizeof(t_GDTEntry) * 7) - 1;
	GDTPtr->base = (uint32_t)&GDT;

	GDT[0] = (t_GDTEntry){0}; // NULL descriptor
	GDT[1] = create_descriptor(0, 0xFFFFF, 0x9A); // Kernel code
	GDT[2] = create_descriptor(0, 0xFFFFF, 0x92); // Kernel data
	GDT[3] = create_descriptor(0, 0xFFFFF, 0x92); // Kernel stack
	GDT[4] = create_descriptor(0, 0xFFFFF, 0xFA); // User code
	GDT[5] = create_descriptor(0, 0xFFFFF, 0xF2); // User data
	GDT[6] = create_descriptor(0, 0xFFFFF, 0xF2); // User stack

	load_gdt((void *)GDTPtr);
}

int main(void)
{
	clear_screen();
	init_GDT();
	printk(GDTPtr);
	return (1);
}
