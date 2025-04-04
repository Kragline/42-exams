int ft_is_valid(char c, int str_base)
{
	int i = 0;
	char *lcase = "0123456789abcdef";
	char *ucase = "0123456789ABCDEF";

	while (i < str_base)
	{
		if (c == lcase[i] || c == ucase[i])
			return (1);
		i++;
	}
	return (0);
}

int	ft_atoi_base(const char *str, int str_base)
{
	int res = 0;
	int sign = 1;

	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (ft_is_valid(*str, str_base))
	{
		res *= str_base;

		if (*str >= '0' && *str <= '9')
			res += *str - '0';
		else if (*str >= 'a' && *str <= 'f')
			res += *str - 'a' + 10;
		else if (*str >= 'A' && *str <= 'F')
			res += *str - 'A' + 10;
			
		str++;
	}
	return (res * sign);
}

#include <stdio.h>
int main(void)
{
	printf("%d\n", ft_atoi_base("+0", 10));
	printf("%d\n", ft_atoi_base("-0", 10));
	printf("%d\n", ft_atoi_base("-125", 10));
	printf("%d\n", ft_atoi_base("-7D", 16));
	printf("%d\n", ft_atoi_base("2147", 10));
	printf("%d\n", ft_atoi_base("863", 16));
}