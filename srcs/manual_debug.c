/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manual_debug.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <mfroehly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 20:41:42 by mfroehly          #+#    #+#             */
/*   Updated: 2016/01/12 20:41:45 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	prev(t_app *app)
{
	if (app->out != 1)
	{
		do_reverse_command(app, app->cursor->command);
		if (app->cursor->previous)
			app->cursor = app->cursor->previous;
		else
			app->out = 1;
	}
}

static void	nex(t_app *app)
{
	if (app->cursor->next)
	{
		if (app->out != 1)
			app->cursor = app->cursor->next;
		app->out = 0;
		do_command(app, app->cursor->command);
	}
}

void	manual_debug(t_app *app)
{
	char	tmp[20];

	resolution(app);
	app->cursor = app->last_resol;
	while (1)
	{
		make_dec(app);
		make_costs(app);
		print_stacks_details(app);
		ft_bzero(tmp, 20);
		read(0, tmp, 20);
		if (ft_memcmp(tmp, "p", 1) == 0)
			prev(app);
		else if (ft_memcmp(tmp, "next", 4) == 0 || ft_memcmp(tmp, "n", 1) == 0)
			nex(app);
		else if (ft_memcmp(tmp, "exit", 4) == 0)
			break ;
	}
}
