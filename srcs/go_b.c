/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_b.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <mfroehly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 20:19:10 by mfroehly          #+#    #+#             */
/*   Updated: 2016/01/17 08:09:43 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	go_b2(t_app *app, t_elem *tmp, t_elem *tmp2, t_elem *move)
{
	unsigned int i;

	i = 0;
	while (tmp2 && tmp2->pre_nbr != tmp->pre_nbr)
	{
		tmp2 = tmp2->previous;
		i++;
	}
	if (tmp2)
	{
		tmp = (tmp->pre_next) ? tmp->pre_next : app->pre;
		move->distance_a = (i <= app->a.size / 2) ? i : i - app->a.size;
	}
	else
		move->distance_a = 0;
	tmp2 = app->b.first;
	i = 0;
	while (tmp2 && tmp2->pre_nbr != tmp->pre_nbr)
	{
		tmp2 = tmp2->previous;
		i++;
	}
	move->distance_b = (i <= app->b.size / 2) ? i : i - app->b.size;
}

void		go_b(t_app *app)
{
	t_elem *tmp;
	t_elem *tmp2;
	t_elem move;

	move.distance_b = 0;
	tmp = app->pre;
	tmp2 = app->a.first;
	if (tmp->what_stack == 0)
		while (tmp->pre_next->what_stack == 0)
			tmp = (tmp->pre_next) ? tmp->pre_next : app->pre;
	else
		while (tmp->what_stack != 0)
			tmp = pre_previous(app, tmp);
	go_b2(app, tmp, tmp2, &move);
	go(app, &move);
}
