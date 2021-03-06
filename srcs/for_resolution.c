/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_resolution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <mfroehly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 20:37:55 by mfroehly          #+#    #+#             */
/*   Updated: 2016/01/17 08:15:52 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	make_dec(t_app *app)
{
	int		i;
	t_elem	*tmp;
	t_elem	*tmp2;

	tmp = app->a.last;
	while (tmp)
	{
		if (tmp->next)
			tmp2 = tmp->next;
		else
			tmp2 = app->a.last;
		i = tmp->pre_nbr - tmp2->pre_nbr;
		i = (i >= 0) ? i : i + (int)app->nbr_nb;
		if (tmp->next)
			tmp->next->dec = i;
		else
			app->a.last->dec = i;
		tmp = tmp->next;
	}
}

void	count_to_b(t_app *app)
{
	t_elem	*tmp;
	int		i;

	i = 0;
	tmp = app->a.last;
	while (tmp)
	{
		if (tmp->generation != 0)
			i++;
		tmp = tmp->next;
	}
	app->nbr_to_b = i;
}

void	last_swap(t_app *app)
{
	t_elem *tmp;

	tmp = app->a.first;
	make_costs(app);
	tmp = app->low_cost;
	go(app, tmp);
	if (app->next_cmd == 1)
	{
		insert_command(app, SA);
		swap(&app->a);
		app->nb_cmd++;
		return ;
	}
}

void	recup_dans_b(t_app *app)
{
	t_elem *tmp;

	tmp = app->a.first;
	make_costs(app);
	tmp = app->low_cost;
	go(app, tmp);
	if (app->next_cmd == 1)
	{
		insert_command(app, SA);
		swap(&app->a);
		app->nb_cmd++;
		return ;
	}
	else if (app->next_cmd == 2)
	{
		insert_command(app, PB);
		push(&app->b, &app->a);
		app->nb_cmd++;
	}
}
