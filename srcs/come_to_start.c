/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   come_to_start.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <mfroehly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 20:10:05 by mfroehly          #+#    #+#             */
/*   Updated: 2016/01/12 20:12:10 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_elem	*min_stack(t_stack *stack)
{
	int i;
	t_elem *rt;
	t_elem *tmp;

	i = 2147483647;
	tmp = stack->first;
	while (tmp)
	{
		if (i > tmp->pre_nbr)
		{
			i = tmp->pre_nbr;
			rt = tmp;
		}
		tmp = tmp->previous;
	}
	return (rt);
}

t_elem	*max_stack(t_stack *stack)
{
	int i;
	t_elem *rt;
	t_elem *tmp;

	i = 0;
	tmp = stack->first;
	while (tmp)
	{
		if (i < tmp->pre_nbr)
		{
			i = tmp->pre_nbr;
			rt = tmp;
		}
		tmp = tmp->previous;
	}
	return (rt);
}
void	come_to_start(t_app *app)
{
	t_elem move;
	t_elem *tmp;
	int i;

	tmp = app->a.first;
	i = 0;
	while (tmp->pre_nbr !=  min_stack(&app->a)->pre_nbr)
	{
		i++;
		tmp = tmp->previous;
	}
	move.distance_a = (i <= app->a.size / 2) ? i : i - app->a.size;
	i = 0;
	move.distance_b = 0;
	if (app->b.first)
	{
		tmp = app->b.first;
		while (tmp->pre_nbr !=  max_stack(&app->b)->pre_nbr)
		{
			i++;
			tmp = tmp->previous;
		}
		move.distance_b = (i <= app->b.size / 2) ? i : i - app->b.size;
	}
	go(app, &move);
}
