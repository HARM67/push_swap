#include "push_swap.h"

t_elem	*new_elem(long int data, t_elem *previous)
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

void	control_double(t_stack *stack)
{
	t_elem *elem;
	t_elem *elem2;

	elem = stack->last;
	elem2 = stack->last;
	while (elem)
	{
		while (elem2)
		{
			if (elem != elem2 && elem->nbr == elem2->nbr)
				put_error();
			elem2 = elem2->next;
		}
		elem2 = stack->last;
		elem = elem->next;
	}
}

int		control_arg(char *str)
{
	if (ft_strtest(str, ft_isdigit))
		return (1);
	if (*str == '-' && ft_strtest(str + 1, ft_isdigit))
		return (1);
	return (0);
}
