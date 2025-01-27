#pragma once

#define VGA_ADDRESS 0x000B8000
#define BLACK 0
#define BLUE 1
#define GREEN 2
#define RED 4
#define WHITE_COLOR 15

#define GDT_ADDRESS 0x00000800

void ft_putnbr_base(unsigned int nb, char *base);

void print_char(char c, unsigned char color);
void print_string(char* str, unsigned char color);


