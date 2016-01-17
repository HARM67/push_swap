/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   need_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <mfroehly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 16:08:35 by mfroehly          #+#    #+#             */
/*   Updated: 2016/01/17 08:03:59 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	try_swap(t_app *app, t_elem *tmp)
{
	t_elem	*p;
	t_elem	*s;
	int		p_new;
	int		a_new;
	int		s_new;

	p = (tmp->previous) ? tmp->previous : app->a.first;
	s = (tmp->next) ? tmp->next : app->a.last;
	a_new = app->nbr_nb - tmp->dec;
	p_new = (p->dec + tmp->dec) % app->nbr_nb;
	s_new = (s->dec + tmp->dec) % app->nbr_nb;
	p->dec = p_new;
	s->dec = s_new;
	tmp->dec = a_new;
}

static void	to_move_b(t_app *app)
{
	t_elem	*tmp;

	tmp = app->a.last;
	while (tmp)
	{
		if (tmp->generation != 0)
		{
			app->nbr_to_b++;
			tmp->move_b = 1;
		}
		tmp = tmp->next;
	}
}

int			need_swap(t_app *app)
{
	t_elem	*tmp;
	t_elem	*tmp2;
	int		i;

	i = 0;
	tmp2 = app->a.first;
	tmp = tmp2;
	while (1)
	{
		if (tmp2->gain == 1)
		{
			tmp2->need_swap = 1;
			(previous(app, tmp2))->need_swap = 2;
			try_swap(app, tmp2);
			calc_stat(app);
			i++;
		}
		tmp2 = (tmp2->previous) ? tmp2->previous : app->a.first;
		if (tmp == tmp2)
			break ;
	}
	to_move_b(app);
	return (0);
}
