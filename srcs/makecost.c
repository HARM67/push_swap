/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   makecost.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <mfroehly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 19:04:24 by mfroehly          #+#    #+#             */
/*   Updated: 2016/01/12 20:06:47 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	good_in_b(t_app *app, t_elem *elem, t_elem *position)
{
	t_elem *tmp;
	t_elem *tmp2;

	tmp = position;
	tmp2 = previous(app, tmp);
	if (tmp == tmp2)
		return (1);
	while (tmp != tmp2)
	{
		if (elem->pre_nbr == tmp->pre_nbr)
			return (1);
		tmp = (tmp->pre_next) ? tmp->pre_next : app->pre;
	}
	return (0);
}


static int		dest_b(t_app *app, t_elem *tmp)
{
	t_elem *tmp2;
	int dest;

	dest = 0;
	tmp2 = app->b.last;
	while (tmp2 && !good_in_b(app, tmp, tmp2))
	{
		tmp2 = previous(app, tmp2);
		dest++;
	}
	if (dest > app->b.size / 2)
		dest -= app->b.size;
	return (dest);
}

static void	make_cost(t_elem *elem)
{
	if (elem->distance_a > 0 && elem->distance_b > 0)
		elem->cost = (elem->distance_a > elem->distance_b) ?
			elem->distance_a : elem->distance_b;
	else if (elem->distance_a < 0 && elem->distance_b < 0)
		elem->cost = (elem->distance_a < elem->distance_b) ?
			-elem->distance_a: -elem->distance_b;
	else
		elem->cost = ABS(elem->distance_a) + ABS( elem->distance_b);
}

void	routine(t_app *app, t_elem *tmp, int *low)
{
	if (tmp->cost < *low && tmp->need_swap && previous(app, tmp)->need_swap == 2)
	{
		*low = tmp->cost;
		app->low_cost = tmp;
		tmp->distance_b = 0;
		app->next_cmd = 1;
	}
	else if (tmp->cost < *low && tmp->move_b && tmp->need_swap == 0)
	{
		*low = tmp->cost;
		app->low_cost = tmp;
		app->next_cmd = 2;
	}
}

void	make_costs(t_app *app)
{
	int i;
	t_elem *tmp;
	int size;
	int low;

	size = app->a.size;
	low = 2147483647;
	tmp = app->a.first;
	i = 0;
	app->next_cmd = 0;
	if (size == 1)
	{
		app->low_cost = tmp;
		return ;
	}
	while (i < size && i < low)
	{
			tmp->distance_a = (i > app->a.size / 2) ? i - app->a.size: i;
			tmp->distance_b = dest_b(app, tmp);
			make_cost(tmp);
		routine(app, tmp, &low);
		tmp = previous(app, tmp);
		i++;
	}
}
