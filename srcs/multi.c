#include "push_swap.h"

void	multi_push(unsigned int nb, t_stack *dest, t_stack *src)
{
	int i;

	i = 0;
	while (i < nb)
	{
		push(dest, src);
		i++;
	}
}

void	multi_swap(unsigned int nb, t_stack *stack)
{
	int i;

	i = 0;
	while (i < nb)
	{
		swap(stack);
		i++;
	}
}
void	multi_rotate(unsigned int nb, t_stack *stack)
{
	int i;

	i = 0;
	while (i < nb)
	{
		rotate(stack);
		i++;
	}
}
void	multi_reverse(unsigned int nb, t_stack *stack)
{
	int i;

	i = 0;
	while (i < nb)
	{
		reverse_rotate(stack);
		i++;
	}
}
