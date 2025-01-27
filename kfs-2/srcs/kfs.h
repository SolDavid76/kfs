#pragma once

#include "int.h"

#define VGA_ADDRESS 0x000B8000
#define BLACK 0
#define BLUE 1
#define GREEN 2
#define RED 4
#define WHITE 15

#define GDT_ADDRESS 0x00000800


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

void ft_putnbr_base(unsigned int nb, char *base);

void clear_screen(void);
void print_char(char c, unsigned char color);
void print_string(char* str, unsigned char color);
void printk(void *GDTPtr);
