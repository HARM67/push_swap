#include "push_swap.h"

int		manual_swap(t_app *app, char *tmp)
{
	int	rt;

	rt = 2;
	if (ft_memcmp(tmp, "sa", 2) == 0)
		swap(&(app->a));
	else if (ft_memcmp(tmp, "sb", 2) == 0)
		swap(&(app->b));
	else if (ft_memcmp(tmp, "ss", 2) == 0)
	{
		swap(&(app->a));
		swap(&(app->b));
	}
	else
		rt = 0;
	return (rt);
}

int		manual_push(t_app *app, char *tmp)
{
	int	rt;

	rt = 2;
	if (ft_memcmp(tmp, "pa", 2) == 0)
		push(&(app->a), &(app->b));
	else if (ft_memcmp(tmp, "pb", 2) == 0)
		push(&(app->b), &(app->a));
	else
		rt = 0;
	return (rt);
}

int		manual_rotate(t_app *app, char *tmp)
{
	int	rt;

	rt = 2;
	if (ft_memcmp(tmp, "ra", 2) == 0)
		rotate(&(app->a));
	else if (ft_memcmp(tmp, "rb", 2) == 0)
		rotate(&(app->b));
	else if (ft_memcmp(tmp, "rr", 2) == 0)
	{
		rotate(&(app->a));
		rotate(&(app->b));
	}
	else
		rt = 0;
	return (rt);
}

int		manual_reverse_rotate(t_app *app, char *tmp)
{
	int	rt;

	rt = 3;
	if (ft_memcmp(tmp, "rra", 3) == 0)
		reverse_rotate(&(app->a));
	else if (ft_memcmp(tmp, "rrb", 3) == 0)
		reverse_rotate(&(app->b));
	else if (ft_memcmp(tmp, "rrr", 3) == 0)
	{
		reverse_rotate(&(app->a));
		reverse_rotate(&(app->b));
	}
	else
		rt = 0;
	return (rt);
}

void	manual(t_app *app)
{
	char	tmp[5];

	while (1)
	{
		print_stacks(app);
		ft_bzero(tmp, 5);
		read(0, tmp, 5);
		if (manual_swap(app, tmp));
		else if (manual_push(app, tmp));
		else if (manual_reverse_rotate(app, tmp));
		else if (manual_rotate(app, tmp));
		else if (ft_memcmp(tmp, "exit", 4) == 0)
			break ;
	}
}
