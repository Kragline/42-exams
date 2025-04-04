#include <unistd.h>

void ft_putchar(char c)
{
	write(1, &c, 1);
}

void ft_putnbr(int n)
{
	if (n == -2147483648)
		write(1, "-2147483648", 11);
	if (n < 0)
	{
		write(1, "-", 1);
		n = -n;
	}
	if (n > 9)
		ft_putnbr(n / 10);
	ft_putchar(n % 10 + '0');
}

int main(void)
{
    ft_putnbr(-2000);
    write(1, "\n", 1);    
    ft_putnbr(215);
    write(1, "\n", 1);    
    ft_putnbr(826);
    write(1, "\n", 1);    
    ft_putnbr(0);
    write(1, "\n", 1);    
    ft_putnbr(7);
    write(1, "\n", 1);    
    return (0);
}