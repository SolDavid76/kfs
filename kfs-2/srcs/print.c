#include "kfs.h"

extern unsigned short	*terminal_buffer;
extern unsigned int 	vga_column;
extern unsigned int 	vga_row;
extern t_GDTEntry		GDT[7];

void clear_screen(void)
{
	for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT * 2; i++)
		terminal_buffer[i] = ' ';
}

void print_char(char c, uint8_t color)
{
	if (c == '\n')
	{
		vga_row += 1;
		vga_column = -1;
	}
	else 
		terminal_buffer[get_vga_index()] = (unsigned short)c | (unsigned short)color << 8;
	vga_column++;
}

void print_string(char* str, uint8_t color)
{
	for (int i = 0; str[i]; i++)
		print_char(str[i], color);
}

void print_number(unsigned int nb, char *base, uint8_t color)
{
	int len = ft_strlen(base);

	if (nb < len)
		print_char(base[nb], color);
	if (nb >= len)
	{
		print_number(nb / len, base, color);
		print_number(nb % len, base, color);
	}
}

void	print_addr(uint32_t p) {
	print_string("0x", RED);
	print_number(p, BASE_16, RED);
}

void	print_GDTEntry(int index)
{
	print_string("\nGDT[", WHITE);
	print_number(index, BASE_10, WHITE);
	print_string("] :\nBase= ", WHITE);
	print_addr((uint32_t)(GDT[index].base_low + (GDT[index].base_mid << 16) + (GDT[index].base_high << 24)));
	print_string(" , Limit= ", WHITE);
	print_addr(GDT[index].limit_low);
	print_string(" , Granularity= ", WHITE);
	print_number(GDT[index].granularity, BASE_16, WHITE);
	print_string("\nAccess= ", WHITE);
	print_number(GDT[index].access, BASE_2, GREEN);
	print_string("\nStack Address=", WHITE);
	print_addr((uint32_t)&GDT[index]);
	print_string("\n", WHITE);
}

void printk(t_GDT *GDTPtr)
{
	print_string("Welcome to KFS-2\n", WHITE);

	print_string("GDTPtr:\nAddress = ", WHITE);
	print_addr((unsigned int)GDTPtr);
	print_string(", GDTPtr.base = ", WHITE);
	print_addr((unsigned int)(GDTPtr->base));
	print_string(", GDTPtr.limit = ", WHITE);
	print_number(GDTPtr->limit, BASE_10, WHITE);
	print_string("\n", WHITE);


	for(int i = 0; i < 7; i++)
		print_GDTEntry(i);
}

