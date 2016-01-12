/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <mfroehly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 19:54:32 by mfroehly          #+#    #+#             */
/*   Updated: 2016/01/12 19:58:42 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	go_reverse(t_app *app, t_elem *elem)
{
	while (elem->distance_a < 0 || elem->distance_b < 0)
	{
		if (elem->distance_b < 0 && elem->distance_a < 0)
		{
			reverse_rotate(&app->a);
			reverse_rotate(&app->b);
			elem->distance_a++;
			elem->distance_b++;
			app->nb_cmd++;
		}
		else if (elem->distance_a < 0)
		{
			reverse_rotate(&app->a);
			elem->distance_a++;
			app->nb_cmd++;
		}
		else if (elem->distance_b < 0)
		{
			reverse_rotate(&app->b);
			elem->distance_b++;
			app->nb_cmd++;
		}
	}
}

void		go(t_app *app, t_elem *elem)
{
	while (elem->distance_a > 0 || elem->distance_b > 0)
	{
		if (elem->distance_b > 0 && elem->distance_a > 0)
		{
			rotate(&app->a);
			rotate(&app->b);
			elem->distance_a--;
			elem->distance_b--;
			app->nb_cmd++;
		}
		else if (elem->distance_a > 0)
		{
			rotate(&app->a);
			elem->distance_a--;
			app->nb_cmd++;
		}
		else if (elem->distance_b > 0)
		{
			rotate(&app->b);
			elem->distance_b--;
			app->nb_cmd++;
		}
	}
	go_reverse(app, elem);
}
