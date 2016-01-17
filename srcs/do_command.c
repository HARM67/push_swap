/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <mfroehly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/17 08:20:44 by mfroehly          #+#    #+#             */
/*   Updated: 2016/01/17 09:23:05 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	do_command2(t_app *app, unsigned int command)
{
	if (command == SA)
		swap(&app->a);
	else if (command == SB)
		swap(&app->b);
	else if (command == SS)
	{
		swap(&app->a);
		swap(&app->b);
	}
	else if (command == PA)
		push(&app->a, &app->b);
	else if (command == PB)
		push(&app->b, &app->a);
}

void		do_command(t_app *app, unsigned char command)
{
	if (command == RA)
		rotate(&app->a);
	else if (command == RB)
		rotate(&app->b);
	else if (command == RR)
	{
		rotate(&app->a);
		rotate(&app->b);
	}
	else if (command == RRA)
	{
		reverse_rotate(&app->a);
	}
	else if (command == RRB)
		reverse_rotate(&app->b);
	else if (command == RRR)
	{
		reverse_rotate(&app->a);
		reverse_rotate(&app->b);
	}
	else
		do_command2(app, command);
}

void		do_reverse_command(t_app *app, unsigned char command)
{
	if (command >= RA && command <= RR)
		do_command(app, command + 3);
	else if (command >= RRA && command <= RRR)
		do_command(app, command - 3);
	else if (command == PA)
		do_command(app, command + 1);
	else if (command == PB)
		do_command(app, command - 1);
	else
		do_command(app, command);
}
