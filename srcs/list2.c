/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <mfroehly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/17 08:09:06 by mfroehly          #+#    #+#             */
/*   Updated: 2016/01/17 08:09:07 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	read_elem(t_app *app, int i, unsigned int nbr_nb)
{
	app->a.first = new_elem(ft_atoi_8((app->av)[i]), app->a.first);
	app->a.first->read_nbr = nbr_nb + 1;
	if (app->a.first->nbr > 2147483647
		|| app->a.first->nbr < -2147483648
		|| !control_arg((app->av)[i]))
		put_error();
}

void	set_stack_numbers(t_app *app)
{
	t_elem	*tmp;
	int		i;

	i = 0;
	tmp = app->a.last;
	while (tmp)
	{
		tmp->current_nbr = i;
		tmp = tmp->next;
		i++;
	}
	tmp = app->b.last;
	while (tmp)
	{
		tmp->current_nbr = -1;
		tmp = tmp->next;
	}
}
