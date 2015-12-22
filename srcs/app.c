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
	manual(app);
}

void	free_app(t_app **app)
{
	free_stack(*app);
	if (*app)
		free(*app);
}
