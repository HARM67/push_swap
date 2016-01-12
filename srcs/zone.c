/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <mfroehly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 16:01:17 by mfroehly          #+#    #+#             */
/*   Updated: 2016/01/12 16:04:36 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	zone_size(t_app *app, t_elem *tmp)
{
	int i;
	int j;
	t_elem *tmp2;

	tmp2 = tmp;
	i = 0;
	j = 0;
	while (i < app->nbr_nb)
	{
		i += tmp2->dec;
		j++;
		tmp2 = (tmp2->next) ? tmp2->next : app->a.last;
	}
	tmp = (tmp->previous) ? tmp->previous : app->a.first;
	tmp->zone_size = j;
}

void		zones_size(t_app *app)
{
	t_elem *tmp;

	tmp = app->a.last;
	while (tmp)
	{
		zone_size(app, tmp);
		tmp = tmp->next;
	}
}

void	select_zone(t_app *app)
{
	t_elem	*tmp;
	t_elem *tmp2;
	int	zone;

	zone = 0;
	tmp = app->a.last;
	tmp2 = tmp;
	while (tmp)
	{
		if (tmp2->zone_size < tmp->zone_size ||(
				tmp2->zone_size == tmp->zone_size &&
				tmp2->pre_nbr > tmp->pre_nbr))
			tmp2 = tmp;
		tmp = tmp->next;
	}
	app->zone_select = tmp2;
}
