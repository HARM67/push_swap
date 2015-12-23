#include "push_swap.h"

void	manual(t_app *app)
{
	char tmp[5];

	while (1)
	{
		print_stacks(app);
		ft_bzero(tmp, 5);
		read(0, tmp, 5);
		if (ft_memcmp(tmp, "sa", 2) == 0)
			swap(&(app->a));
		else if (ft_memcmp(tmp, "sb", 2) == 0)
			swap(&(app->b));
		else if (ft_memcmp(tmp, "ss", 2) == 0)
		{
			swap(&(app->a));
			swap(&(app->b));
		}
		else if (ft_memcmp(tmp, "pa", 2) == 0)
			push(&(app->a), &(app->b));
		else if (ft_memcmp(tmp, "pb", 2) == 0)
			push(&(app->b), &(app->a));
		else if (ft_memcmp(tmp, "rra", 3) == 0)
			reverse_rotate(&(app->a));
		else if (ft_memcmp(tmp, "rrb", 3) == 0)
			reverse_rotate(&(app->b));
		else if (ft_memcmp(tmp, "rrr", 3) == 0)
		{
			reverse_rotate(&(app->a));
			reverse_rotate(&(app->b));
		}
		else if (ft_memcmp(tmp, "ra", 2) == 0)
			rotate(&(app->a));
		else if (ft_memcmp(tmp, "rb", 2) == 0)
			rotate(&(app->b));
		else if (ft_memcmp(tmp, "rr", 2) == 0)
		{
			rotate(&(app->a));
			rotate(&(app->b));
		}
		else if (ft_memcmp(tmp, "exit", 4) == 0)
			break ;
	}
}
