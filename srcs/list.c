#include "push_swap.h"

t_elem	*new_elem(int data, t_elem *previous)
{
	t_elem	*elem;

	elem = (t_elem*)ft_memalloc(sizeof(t_elem));
	if (elem == 0)
		put_error();
	elem->nbr = data;
	elem->previous = previous;
	if (previous)
		previous->next = elem;
	return (elem);
}

void	conform_stack(t_stack *stack)
{
	t_elem *tmp;

	tmp = stack->first;
	if (tmp == 0)
	{
		ft_bzero(stack, sizeof(t_stack));
		return ;
	}
	while (tmp->previous)
		tmp = tmp->previous;
	stack->last = tmp;
	while (tmp->next)
		tmp = tmp->next;
	stack->first = tmp;
	if (stack->first->previous)
		stack->second = stack->first->previous;
}

void	read_arg(t_app *app)
{
	unsigned int	i;
	unsigned int	nbr_nb;
	t_elem			*tmp;


	tmp = 0;
	i = 1;
	nbr_nb = 0;
	while (i < app->ac)
	{
		if (ft_isdigit(**(app->av)))
			put_error();
		app->a.first = new_elem(ft_atoi((app->av)[i]), app->a.first);
		i++;
		nbr_nb++;
	}
	conform_stack(&(app->a));
	app->nbr_nb = nbr_nb;
}

void	print_stacks(t_app *app)
{
	if (control(app) == 1)
		ft_printf("{FG_GREEN}{DARK}");
	else if (control(app) == 2)
		ft_printf("{FG_YELLOW}");
	else
		ft_printf("{FG_RED}");
	ft_printf("a : ");
	print_stack(&(app->a));
	ft_printf("\nb : ");
	print_stack(&(app->b));
	ft_printf("\n\n");
	ft_printf("{EOC}");
}

void	print_stack(t_stack *stack)
{
	t_elem *tmp;

	tmp = stack->last;
	while (tmp)
	{
		ft_printf("%3d ", tmp->nbr);
		tmp = tmp->next;
	}
}
