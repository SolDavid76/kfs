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

void print_number(uint32_t nb, char *base, uint8_t color)
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

void	print_addr(uint32_t p)
{
	print_string("0x", RED);
	print_number(p, BASE_16, RED);
}

void	print_GDTEntry(int index)
{
	print_string("\nGDT[", WHITE);
	print_number(index, BASE_10, WHITE);
	print_string("] : Base= ", WHITE);
	print_addr((uint32_t)(GDT[index].base_low + (GDT[index].base_mid << 16) + (GDT[index].base_high << 24)));
	print_string(" , Limit= ", WHITE);
	print_addr(GDT[index].limit_low);
	print_string(" , Granularity= ", WHITE);
	print_number(GDT[index].granularity, BASE_16, WHITE);
	print_string("\nAccess= ", WHITE);
	print_number(GDT[index].access, BASE_2, GREEN);
	print_string("\n", WHITE);
}

extern uint32_t get_stack_pointer();

void print_stack(uint32_t num_entries)
{
    uint32_t *stack_ptr = (uint32_t *)get_stack_pointer();
	// int a = 42;
	// int b = 1234;

    print_string("Kernel Stack:\n", WHITE);

    for (uint32_t i = 0; i < num_entries; i++) {
        uint32_t value = stack_ptr[i];
		print_string("ESP+",WHITE);
		print_number(i * 4, BASE_10, WHITE);
		print_string(": ", WHITE);
		print_number(value, BASE_10, WHITE);
		print_string("\n", WHITE);
    }
}

void printk(t_GDT *GDTPtr)
{
	print_string("Welcome to KFS-2", WHITE);
	print_GDTEntry(1);
	print_stack(21);
}
