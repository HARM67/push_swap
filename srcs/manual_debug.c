/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manual_debug.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <mfroehly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 20:41:42 by mfroehly          #+#    #+#             */
/*   Updated: 2016/01/17 11:06:14 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	prev(t_app *app, unsigned int i)
{
	unsigned int pos;

	pos = 0;
	if (!app->cursor)
		return ;
	while (app->out != 1 && pos < i)
	{
		do_reverse_command(app, app->cursor->command);
		if (app->cursor->previous)
			app->cursor = app->cursor->previous;
		else
			app->out = 1;
		pos++;
	}
}

static void	nex(t_app *app, unsigned int i)
{
	unsigned int pos;

	pos = 0;
	if (!app->cursor)
		return ;
	while ((app->cursor->next || app->out == 1) && pos < i)
	{
		if (app->out != 1)
			app->cursor = app->cursor->next;
		app->out = 0;
		do_command(app, app->cursor->command);
		pos++;
	}
}

static void	start(t_app *app)
{
	if (!app->cursor)
		return ;
	while (app->out != 1)
	{
		prev(app, 1);
	}
}

static void	end(t_app *app)
{
	if (!app->cursor)
		return ;
	while (app->cursor->next || app->out == 1)
	{
		nex(app, 1);
	}
}

void		manual_debug(t_app *app)
{
	char	tmp[20];

	resolution(app);
	app->cursor = app->last_resol;
	while (1)
	{
		make_dec(app);
		make_costs(app);
		ft_printf("piece la moin chere %d\n", app->low_cost->nbr);
		print_stacks_details(app);
		ft_bzero(tmp, 20);
		read(0, tmp, 20);
		if (ft_memcmp(tmp, "p", 1) == 0)
			prev(app, (*(tmp + 1) != 10) ? ft_atoi(tmp + 1) : 1);
		else if (ft_memcmp(tmp, "n", 1) == 0)
			nex(app, (*(tmp + 1) != 10) ? ft_atoi(tmp + 1) : 1);
		else if (ft_memcmp(tmp, "start", 5) == 0 || ft_memcmp(tmp, "s", 1) == 0)
			start(app);
		else if (ft_memcmp(tmp, "end", 3) == 0 || ft_memcmp(tmp, "e", 1) == 0)
			end(app);
		else if (ft_memcmp(tmp, "exit", 4) == 0)
			break ;
	}
}
