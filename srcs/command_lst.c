/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_lst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <mfroehly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/17 08:22:10 by mfroehly          #+#    #+#             */
/*   Updated: 2016/01/17 08:22:11 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void		insert_command(t_app *app, unsigned char command)
{
	t_comm	*comm;

	comm = (t_comm*)ft_memalloc(sizeof(t_comm));
	if (!comm)
		exit(1);
	comm->command = command;
	if (!app->resolution)
	{
		app->resolution = comm;
		app->last_resol = comm;
	}
	else if (app->last_resol)
	{
		comm->previous = app->last_resol;
		app->last_resol->next = comm;
		app->last_resol = comm;
	}
	app->nb_cmd2++;
	app->nb_cmd_tab[command]++;
}

static void	print_command(unsigned char command)
{
	if (command == RA)
		ft_putstr("ra");
	else if (command == RB)
		ft_putstr("rb");
	else if (command == RR)
		ft_putstr("rr");
	else if (command == RRA)
		ft_putstr("rra");
	else if (command == RRB)
		ft_putstr("rrb");
	else if (command == RRR)
		ft_putstr("rrr");
	else if (command == SA)
		ft_putstr("sa");
	else if (command == SB)
		ft_putstr("sb");
	else if (command == SS)
		ft_putstr("ss");
	else if (command == PA)
		ft_putstr("pa");
	else if (command == PB)
		ft_putstr("pb");
}

void		print_commands(t_app *app)
{
	t_comm	*comm;

	comm = app->resolution;
	while (comm)
	{
		print_command(comm->command);
		if (comm->next != 0)
			ft_putstr(" ");
		comm = comm->next;
	}
	ft_putstr("\n");
}
