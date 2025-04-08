#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>

void put_string(char *str, int *length)
{
	if (!str)
		str = "(null)";
	while (*str)
		*length += write(1, str++, 1);	
}

void put_digit(long long int number, int base, int *length)
{
	char *hex = "0123456789abcdef";

	if (number < 0)
	{
		number *= -1;
		*length += write(1, "-", 1);
	}
	if (number >= base)
		put_digit((number / base), base, length);
	*length += write(1, &hex[number % base], 1);
}

int ft_printf(const char *format, ... )
{
	va_list pointer;
	va_start(pointer, format);
	int i = 0;
	int length = 0;

	while (format[i])
	{
		if (format[i + 1] && format[i] == '%' && (format[i + 1] == 'd' || format[i + 1] == 's' || format[i + 1] == 'x'))
		{
			i++;
			if (format[i] == 's')
				put_string(va_arg(pointer, char *), &length);
			else if (format[i] == 'd')
				put_digit((long long int)va_arg(pointer, int), 10, &length);
			else if (format[i] == 'x')
				put_digit((long long int)va_arg(pointer, unsigned int), 16, &length);
		}
		else
			length += write(1, &format[i], 1);
		i++;
	}
	return (va_end(pointer), length);
}

int main()
{
	printf("%s %d %x\n", "abcd", 256, 17);
	ft_printf("%s %d %x", "abcd", 256, 17);
}