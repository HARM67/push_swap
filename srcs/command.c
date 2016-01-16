#include "push_swap.h"

void	swap(t_stack *stack)
{
	int tmp;

	if (stack->first == 0 || stack->first->previous == 0 )
		return ;
	stack->first->previous = stack->second->previous;
	stack->second->previous = stack->first;

	stack->first->next = stack->second;
	stack->second->next = 0;
	if (stack->first->previous)
		stack->first->previous->next = stack->first;
	conform_stack(stack);
	stack->first->need_swap = 0;
	stack->second->need_swap = 0;
	tmp = stack->first->move_b;
	stack->first->move_b = stack->second->move_b;
	stack->second->move_b = tmp;
	stack->first->change =1;
	stack->second->change =1;
}

void	push(t_stack *dest, t_stack *src)
{
	t_elem	*tmp;

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
	tmp->what_stack = dest->stack_nbr;
	dest->first = tmp;
	if (tmp->previous)
		tmp->previous->next = tmp;
	conform_stack(src);
	conform_stack(dest);
	if (src->size >= 1)
	(src->size)--;

	(dest->size)++;
	dest->first->change = 1;
}

void	all_highlight(t_stack *stack)
{
	t_elem	*elem;

	elem = stack->last;
	while (elem)
	{
		elem->change = 1;
		elem= elem->next;
	}
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
	conform_stack(stack);
	all_highlight(stack);
}

void reverse_rotate(t_stack *stack)
{
	if (stack->first == 0 || stack->second == 0)
		return ;
	stack->first->next = stack->last;
	stack->last->previous = stack->first;
	stack->last->next->previous = 0;
	stack->last->next = 0;
	conform_stack(stack);
	all_highlight(stack);
}
