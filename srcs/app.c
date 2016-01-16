#include "push_swap.h"

void	init_app(t_app **app, int ac, char **av)
{
	*app = (t_app*)ft_memalloc(sizeof(t_app));
	if (*app == 0)
		put_error();
	(*app)->ac = ac;
	(*app)->av = av;
	init_stack(*app);
	(*app)->best = (*app)->nbr_nb;
}

void	run_app(t_app *app)
{
	pre_resolve(app);
	if (app->file)
		from_file(app);
	else if (app->manual_debug)
		manual_debug(app);
	else if (app->manual)
		manual(app);
	else
		resolution(app);
	if (!app->manual_debug || app->manual || app->file)
		print_commands(app);
}

