/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <mfroehly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/17 07:56:17 by mfroehly          #+#    #+#             */
/*   Updated: 2016/01/17 07:56:18 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	init_stack(t_app *app)
{
	ft_bzero(&(app->a), sizeof(t_stack));
	ft_bzero(&(app->b), sizeof(t_stack));
	app->a.stack_nbr = 0;
	app->b.stack_nbr = 1;
	read_arg(app);
}
