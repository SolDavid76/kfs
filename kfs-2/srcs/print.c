#include "kfs.h"

extern unsigned short	*terminal_buffer;
extern unsigned int 	vga_index;

void clear_screen(void)
{
	for (int i = 0; i < 80 * 25 * 2; i++)
		terminal_buffer[i] = ' ';
}

void print_char(char c, unsigned char color)
{
	terminal_buffer[vga_index] = (unsigned short)c | (unsigned short)color << 8;
	vga_index++;
}

void print_string(char* str, unsigned char color)
{
	for (int i = 0; str[i]; i++)
		print_char(str[i], color);
}

void printk(void *GDTPtr)
{
	ft_putnbr_base((unsigned int)GDTPtr, "0123456789ABCDEF");
}
