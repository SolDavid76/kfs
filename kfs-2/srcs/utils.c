#include "kfs.h"

int ft_strlen(char *str)
{
	int i = 0;

	while (str[i])
		i++;
	return (i);
}

void ft_putnbr_base(int nb, char *base)
{
	int len = ft_strlen(base);

	if (nb < len)
		print_char(base[nb], WHITE_COLOR);
	if (nb >= len)
	{
		ft_putnbr_base(nb / len, base);
		ft_putnbr_base(nb % len, base);
	}
}