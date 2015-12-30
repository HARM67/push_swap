#include "push_swap.h"

void	init_app(t_app **app, int ac, char **av)
{
	*app = (t_app*)ft_memalloc(sizeof(t_app));
	if (*app == 0)
		put_error();
	(*app)->ac = ac;
	(*app)->av = av;
	init_stack(*app);
}

void	run_app(t_app *app)
{
	pre_resolve(app);
	create_table(&app->statistic, app->nbr_nb);
	if (app->file)
		from_file(app);
	else if (app->manual_debug)
		manual_debug(app);
	else if (app->manual)
		manual(app);
	else
		resolve(app);
}

void	free_app(t_app **app)
{
	free_stack(*app);
	if (*app)
		free(*app);
}
