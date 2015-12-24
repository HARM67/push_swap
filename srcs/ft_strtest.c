#include "push_swap.h"

int	ft_strtest(char *str, int (*f)(int))
{
	while (*str)
	{
		if (!f((int)*str))
			return (0);
		str++;
	}
	return (1);
}
