#pragma once

#include "int.h"

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_ADDRESS 0x000B8000
#define BLACK 0
#define BLUE 1
#define GREEN 2
#define RED 4
#define WHITE 15

#define GDT_ADDRESS 0x00000800

#define BASE_2	"01"
#define BASE_10	"0123456789"
#define BASE_16	"0123456789ABCDEF"


typedef struct __attribute__((packed)) s_GDTEntry
{
	uint16_t	limit_low;
	uint16_t	base_low;
	uint8_t		base_mid;
	uint8_t		access;
	uint8_t		granularity;
	uint8_t		base_high;
}				t_GDTEntry;

typedef struct __attribute__((packed)) s_GDT
{
	uint16_t	limit;
	uint32_t	base;
}				t_GDT;

int ft_strlen(char *str);
uint16_t	get_vga_index();


void clear_screen(void);
void print_char(char c, uint8_t color);
void print_string(char* str, uint8_t color);
void print_number(uint32_t nb, char *base, uint8_t color);
void printk(t_GDT *GDTPtr);
