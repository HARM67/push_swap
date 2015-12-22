#include "push_swap.h"

void	init_stack(t_app *app)
{
	ft_bzero(&(app->a), sizeof(t_stack));
	ft_bzero(&(app->b), sizeof(t_stack));
	read_arg(app);
}

void	free_stack(t_app *app)
{
	if (app->a.first)
		free(app->a.first);
	if (app->b.first)
		free(app->b.first);
}

