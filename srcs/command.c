#include "push_swap.h"

void	swap(t_stack *stack)
{
	if (stack->first == 0 || stack->first->previous == 0 )
		return ;
	stack->first->previous = stack->second->previous;
	stack->second->previous = stack->first;

	stack->first->next = stack->second;
	stack->second->next = 0;
	if (stack->first->previous)
		stack->first->previous->next = stack->first;
	conform_stack(stack);
}

void	push(t_stack *dest, t_stack *src)
{
	t_elem *tmp;

	tmp = src->first;
	if (src->first == 0)
		return;
	if (src->first->previous)
	{
		src->first = src->first->previous;
		src->first->next = 0;
	}
	else
		src->first = 0;
	tmp->previous = dest->first;
	dest->first = tmp;
	if (tmp->previous)
		tmp->previous->next = tmp;
	conform_stack(src);
	conform_stack(dest);
}
