/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <mfroehly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 19:54:32 by mfroehly          #+#    #+#             */
/*   Updated: 2016/01/17 08:11:10 by mfroehly         ###   ########.fr       */
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
			insert_command(app, RRR);
		}
		else if (elem->distance_a < 0)
		{
			insert_command(app, RRA);
			reverse_rotate(&app->a);
			elem->distance_a++;
		}
		else if (elem->distance_b < 0)
		{
			insert_command(app, RRB);
			reverse_rotate(&app->b);
			elem->distance_b++;
		}
	}
}

void	go(t_app *app, t_elem *elem)
{
	while (elem->distance_a > 0 || elem->distance_b > 0)
	{
		if (elem->distance_b > 0 && elem->distance_a > 0)
		{
			insert_command(app, RR);
			rotate(&app->a);
			rotate(&app->b);
			elem->distance_a--;
			elem->distance_b--;
		}
		else if (elem->distance_a > 0)
		{
			insert_command(app, RA);
			rotate(&app->a);
			elem->distance_a--;
		}
		else if (elem->distance_b > 0)
		{
			insert_command(app, RB);
			rotate(&app->b);
			elem->distance_b--;
		}
	}
	go_reverse(app, elem);
}
