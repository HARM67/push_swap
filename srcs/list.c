#include "push_swap.h"

t_elem	*new_elem(int data, t_elem *previous)
{
	t_elem	*elem;

	elem = (t_elem*)ft_memalloc(sizeof(t_elem));
	if (elem == 0)
		put_error();
	elem->nbr = data;
	elem->next = 0;
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
	t_elem			*tmp;

	tmp = 0;
	i = 1;
	while (i < app->ac)
	{
		if (ft_isdigit(**(app->av)))
			put_error();
		app->a.first = new_elem(ft_atoi((app->av)[i]), app->a.first);
		i++;
	}
	conform_stack(&(app->a));
}

void	print_stacks(t_app *app)
{
	ft_printf("{FG_GREEN}{BOLD}a : {EOC}");
	print_stack(&(app->a));
	ft_printf("\n{FG_GREEN}{BOLD}b : {EOC}");
	print_stack(&(app->b));
	ft_printf("\n");
}

void	print_stack(t_stack *stack)
{
	t_elem *tmp;

	tmp = stack->last;
	while (tmp)
	{
		ft_printf("%d ", tmp->nbr);
		tmp = tmp->next;
	}
}
