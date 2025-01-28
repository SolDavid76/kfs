#pragma once

#include "int.h"

#define VGA_ADDRESS 0x000B8000
#define BLACK 0
#define BLUE 1
#define GREEN 2
#define RED 4
#define WHITE 15

#define GDT_ADDRESS 0x00000800

#define VGA_WIDTH 80
#define VGA_HEIGHT 25

#define BASE_2	"01"
#define BASE_10	"0123456789"
#define BASE_16	"0123456789ABCDEF"


typedef struct __attribute__((packed)) s_GDTEntry
{
	uint16_t	limit_low; // Limite basse (16 bits)
	uint16_t	base_low; // Base basse (16 bits)
	uint8_t		base_mid; // Base moyenne (8 bits)
	uint8_t		access; // Attributs d'accès
	uint8_t		granularity; // Granularité et bits de limite élevée
	uint8_t		base_high; // Base haute (8 bits)
}				t_GDTEntry;

typedef struct __attribute__((packed)) s_GDT
{
	uint16_t	limit; // Taille de la GDT moins 1
	uint32_t	base; // Adresse de la GDT
}				t_GDT;

int ft_strlen(char *str);
uint16_t	get_vga_index();


void clear_screen(void);
void print_char(char c, uint8_t color);
void print_string(char* str, uint8_t color);
void print_number(unsigned int nb, char *base, uint8_t color);
void printk(t_GDT *GDTPtr);
