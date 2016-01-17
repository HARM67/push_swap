/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_stack.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <mfroehly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 16:07:19 by mfroehly          #+#    #+#             */
/*   Updated: 2016/01/17 08:02:08 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static	void	print_detail(char *str, t_elem *tmp, int dec)
{
	ft_printf("%5s:", str);
	while (tmp)
	{
		ft_printf("%3d ", *(int*)((void*)tmp - dec));
		tmp = tmp->next;
	}
	ft_putchar('\n');
}

static	void	select_color(t_app *app)
{
	if (control(app) == 1)
		ft_printf("{FG_GREEN}{DARK}");
	else if (control(app) == 2)
		ft_printf("{FG_YELLOW}");
	else
		ft_printf("{FG_RED}");
}

static	void	print_stack_details(t_stack *stack, t_app *app)
{
	t_elem	*tmp;

	select_color(app);
	tmp = stack->last;
	while (tmp)
	{
		if (tmp->change)
			ft_printf("{HIGHLIGHT}");
		ft_printf("%3d ", tmp->nbr);
		tmp->change = 0;
		tmp = tmp->next;
	}
	tmp = stack->last;
	ft_printf("{EOC}{FG_BLUE}\n");
	print_detail("pre", tmp, (int)((void *)tmp - (void *)&tmp->pre_nbr));
	print_detail("dec", tmp, (int)((void *)tmp - (void *)&tmp->dec));
	print_detail("gain", tmp, (int)((void *)tmp - (void *)&tmp->gain));
	print_detail("gene", tmp, (int)((void *)tmp - (void *)&tmp->generation));
	print_detail("zoneS", tmp, (int)((void *)tmp - (void *)&tmp->zone_size));
	print_detail("Nswap", tmp, (int)((void *)tmp - (void *)&tmp->need_swap));
	print_detail("moveB", tmp, (int)((void *)tmp - (void *)&tmp->move_b));
	print_detail("distA", tmp, (int)((void *)tmp - (void *)&tmp->distance_a));
	print_detail("distB", tmp, (int)((void *)tmp - (void *)&tmp->distance_b));
	print_detail("cost", tmp, (int)((void *)tmp - (void *)&tmp->cost));
	ft_printf("{EOC}");
}

void			print_stacks_details(t_app *app)
{
	ft_printf("{FG_BLUE}");
	ft_printf("\n{BOLD}    A:{EOC}");
	print_stack_details(&(app->a), app);
	ft_printf("{FG_BLUE}");
	ft_printf("\n{BOLD}    B:{EOC}");
	print_stack_details(&(app->b), app);
	if (app->color)
		ft_printf("{EOC}");
	ft_printf("\n\n");
}
