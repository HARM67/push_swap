/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolution.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <mfroehly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 20:39:51 by mfroehly          #+#    #+#             */
/*   Updated: 2016/01/17 11:42:35 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	boucle2(t_app *app)
{
	while (app->b.size != 0)
	{
		go_b(app);
		insert_command(app, PA);
		push(&app->a, &app->b);
		make_dec(app);
		if (app->debug)
			print_stacks(app);
		app->nb_cmd++;
	}
	come_to_start(app);
	make_dec(app);
	if (app->debug || app->manual_debug)
	{
		print_stacks(app);
		ft_printf("fait en %d commande(s)\n", app->nb_cmd2);
	}
}

static void	boucle(t_app *app)
{
	int i;

	if (app->nbr_nb == 1)
		return ;
	i = 0;
	count_to_b(app);
	while (app->b.size < app->nbr_to_b)
	{
		i++;
		recup_dans_b(app);
		if (app->debug)
			print_stacks(app);
	}
	make_dec(app);
	while (control(app) == 0)
	{
		last_swap(app);
		make_dec(app);
		if (app->debug)
			print_stacks(app);
	}
	boucle2(app);
}

void		resolution(t_app *app)
{
	make_dec(app);
	calc_stat(app);
	need_swap(app);
	make_dec(app);
	make_costs(app);
	boucle(app);
	make_dec(app);
}
