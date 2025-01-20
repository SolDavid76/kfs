#define VGA_ADDRESS 0xB8000
#define BLACK 0
#define BLUE 1
#define GREEN 2
#define RED 4
#define WHITE_COLOR 15

unsigned short* terminal_buffer;
unsigned int vga_index;

void clear_screen(void)
{
	int index = 0;
	while (index < 80 * 25 * 2) {
		terminal_buffer[index] = ' ';
		index++;
	}
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

void main(void)
{
	terminal_buffer = (unsigned short*)VGA_ADDRESS;
	vga_index = 0;
	clear_screen();
	print_string("42", GREEN);
	return;
}
