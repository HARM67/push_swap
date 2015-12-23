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
	stack->first->change =1;
	stack->second->change =1;
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
	dest->first->change = 1;
}

void	rotate(t_stack *stack)
{
	if (stack->first == 0 || stack->second == 0)
		return ;
	stack->first->next = stack->last;
	stack->last->previous = stack->first;
	stack->second->next = 0;
	stack->first->previous = 0;
	stack->first = stack->second;
	ft_printf("ra ");
	conform_stack(stack);
}

void reverse_rotate(t_stack *stack)
{
	if (stack->first == 0 || stack->second == 0)
		return ;
	stack->first->next = stack->last;
	stack->last->previous = stack->first;
	stack->last->next->previous = 0;
	stack->last->next = 0;
	ft_printf("rra ");
	conform_stack(stack);
}
