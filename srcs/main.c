/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <mfroehly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/17 08:08:23 by mfroehly          #+#    #+#             */
/*   Updated: 2016/01/17 09:49:32 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int ac, char **av)
{
	t_app	*app;

	if (ac == 1)
		return (0);
	if (ac < 2)
		put_error();
	app = 0;
	init_app(&app, ac, av);
	run_app(app);
	return (0);
}
