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

/*
void	insert_command(t_app *app, unsigned int command)
{
	t_comm *comm;

	comm = (t_comm*)ft_memalloc(sizeof(t_comm));
	if (!app->resolution)
	{
		app->resolution = comm;
		app->last_resol = comm;
	}
	else if (app->last_resol)
		app->last_resol->next = comm;
}
*/

void	manual_debug(t_app *app)
{
	char	tmp[20];

	make_dec(app);
	calc_stat(app);
	need_swap(app);
	make_dec(app);
	make_costs(app);
	while (1)
	{
		make_dec(app);
		make_costs(app);
		print_stacks_details(app);
		ft_bzero(tmp, 20);
		read(0, tmp, 20);
		system("clear");
		if (manual_swap(app, tmp));
		else if (manual_push(app, tmp));
		else if (manual_reverse_rotate(app, tmp));
		else if (manual_rotate(app, tmp));
		else if (ft_memcmp(tmp, "g", 1) == 0)
			go_b(app);
		else if (ft_memcmp(tmp, "s", 1) == 0)
			last_swap(app);
		else if (ft_memcmp(tmp, "c", 1) == 0)
			come_to_start(app);
		else if (ft_memcmp(tmp, "n", 1) == 0)
			recup_dans_b(app);
		else if (ft_memcmp(tmp, "exit", 4) == 0)
			break ;
	}
}
