int ft_atoi(char *str)
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
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + *str - '0';
		str++;
	}
	return (sign * res);
}

#include <stdlib.h>
#include <stdio.h>
int main(void)
{
    printf("%d\n", atoi("-81475hjc74"));
    printf("%d\n", ft_atoi("-81475hjc74"));
    printf("%d\n", atoi("+4754"));
    printf("%d\n", ft_atoi("+4754"));
    printf("%d\n", atoi("-+74"));
    printf("%d\n", ft_atoi("-+74"));
    printf("%d\n", atoi("+0"));
    printf("%d\n", ft_atoi("+0"));
    return (0);
}
