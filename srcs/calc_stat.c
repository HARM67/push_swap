/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_stat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <mfroehly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 16:05:00 by mfroehly          #+#    #+#             */
/*   Updated: 2016/01/12 16:06:08 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"


static void	calculate_gene(t_app *app)
{
	int i;
	t_elem *tmp;
	t_elem *tmp2;

	i = 0;
	tmp = app->zone_select;
	tmp2 = tmp;
	while (1)
	{
		tmp->generation = i / app->nbr_nb;
		tmp = (tmp->next) ? tmp->next : app->a.last;
		i += tmp->dec;
		if (tmp == tmp2)
			break;
	}
	app->gene_nb = i / app->nbr_nb;
}

static void	make_gain(t_app *app, t_elem *tmp)
{
	t_elem *p;
	t_elem *s;
	int ancien;
	int nouveau;

	p = (tmp->previous) ? tmp->previous : app->a.first;
	s = (tmp->next) ? tmp->next : app->a.last;
	ancien = p->dec + tmp->dec + s->dec;
	nouveau = app->nbr_nb - tmp->dec;
	nouveau += (p->dec + tmp->dec) % app->nbr_nb;
	nouveau += (s->dec + tmp->dec) % app->nbr_nb;
	tmp->gain = (ancien - nouveau) / (int)app->nbr_nb;
}

static void	make_gains(t_app *app)
{
	t_elem *tmp;

	tmp = app->a.last;
	while (tmp)
	{
		make_gain(app, tmp);
		tmp = tmp->next;
	}
}

void	calc_stat(t_app *app)
{
	zones_size(app);
	select_zone(app);
	calculate_gene(app);
	make_gains(app);
}
