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

