/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <mfroehly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/17 08:17:39 by mfroehly          #+#    #+#             */
/*   Updated: 2016/01/17 08:18:57 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void		from_file_command(t_app *app, char **file, int *print, int *coup)
{
	int rt;

	rt = 0;
	print = 0;
	if ((rt = manual_swap(app, *file)))
		(*coup)++;
	else if ((rt = manual_push(app, *file)))
		(*coup)++;
	else if ((rt = manual_reverse_rotate(app, *file)))
		(*coup)++;
	else if ((rt = manual_rotate(app, *file)))
		(*coup)++;
	else
		put_error();
	*file += rt;
}

static void	from_file2(t_app *app)
{
	make_dec(app);
	if (app->debug == 0)
		print_stacks(app);
}

void		from_file(t_app *app)
{
	char	*file;
	int		print;
	int		coup;

	print = 0;
	coup = 0;
	get_next_line(0, &file);
	if (!file)
		put_error();
	while (*file != 0)
	{
		if (print != 0 && *file != ' ')
			put_error();
		if (print != 0 && *file == ' ')
			file++;
		print = 1;
		if (app->debug && print)
			ft_printf("%.3s", file);
		from_file_command(app, &file, &print, &coup);
		if (app->debug && print)
			print_stacks(app);
	}
	from_file2(app);
	if (app->result)
		ft_printf("Il a fallut %d coups\n\n", coup);
}
