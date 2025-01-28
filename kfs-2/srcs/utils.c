#include "kfs.h"

extern unsigned int 	vga_column;
extern unsigned int 	vga_row;

uint16_t	get_vga_index()
{
	if (vga_column >= VGA_WIDTH){
		vga_column -= VGA_WIDTH;
		vga_row += 1; 
	}
	return (vga_column + vga_row * VGA_WIDTH);
}

int ft_strlen(char *str)
{
	int i = 0;

	while (str[i])
		i++;
	return (i);
}
