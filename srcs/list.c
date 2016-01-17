/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <mfroehly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/17 08:09:21 by mfroehly          #+#    #+#             */
/*   Updated: 2016/01/17 08:09:22 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	conform_stack(t_stack *stack)
{
	t_elem *tmp;

	tmp = stack->first;
	if (tmp == 0)
	{
		ft_bzero(stack, sizeof(t_stack));
		return ;
	}
	while (tmp->previous)
		tmp = tmp->previous;
	stack->last = tmp;
	while (tmp->next)
		tmp = tmp->next;
	stack->first = tmp;
	if (stack->first->previous)
		stack->second = stack->first->previous;
}

void	read_param(t_app *app, unsigned int *i)
{
	if (ft_strcmp(app->av[*i], "-v") == 0)
		app->debug = 1;
	else if (ft_strcmp(app->av[*i], "-c") == 0)
		app->color = 1;
	else if (ft_strcmp(app->av[*i], "-md") == 0)
		app->manual_debug = 1;
	else if (ft_strcmp(app->av[*i], "-m") == 0)
		app->manual = 1;
	else if (ft_strcmp(app->av[*i], "-f") == 0)
		app->file = 1;
	else if (ft_strcmp(app->av[*i], "-h") == 0)
		app->highlight = 1;
	else if (ft_strcmp(app->av[*i], "-f") == 0)
		app->file = 1;
	else if (ft_strcmp(app->av[*i], "-r") == 0)
		app->result = 1;
	else
		put_error();
}

void	read_arg(t_app *app)
{
	unsigned int	i;
	unsigned int	nbr_nb;
	t_elem			*tmp;

	tmp = 0;
	i = 1;
	nbr_nb = 0;
	while (i < app->ac)
	{
		if ((*(app->av)[i]) == '-' && !ft_isdigit(*(app->av[i] + 1)))
			read_param(app, &i);
		else
		{
			read_elem(app, i, nbr_nb);
			nbr_nb++;
		}
		i++;
	}
	app->a.size = nbr_nb;
	conform_stack(&(app->a));
	control_double(&(app->a));
	app->nbr_nb = nbr_nb;
}

void	print_stacks(t_app *app)
{
	if (app->color)
		ft_printf("{FG_BLUE}");
	ft_printf("\n{BOLD}a :{EOC}");
	print_stack(&(app->a), app);
	if (app->color)
		ft_printf("{FG_BLUE}");
	ft_printf("\n{BOLD}b :{EOC}");
	print_stack(&(app->b), app);
	if (app->color)
		ft_printf("{EOC}");
	ft_printf("\n\n");
}

void	print_stack(t_stack *stack, t_app *app)
{
	t_elem *tmp;

	tmp = stack->last;
	if (control(app) == 1 && app->color)
		ft_printf("{FG_GREEN}{DARK}");
	else if (control(app) == 2 && app->color)
		ft_printf("{FG_YELLOW}");
	else if (app->color)
		ft_printf("{FG_RED}");
	while (tmp)
	{
		if (tmp->change && app->highlight)
			ft_printf("{HIGHLIGHT}");
		ft_printf("%3d ", tmp->nbr);
		tmp->change = 0;
		tmp = tmp->next;
	}
	if (app->color)
		ft_printf("{EOC}");
}
