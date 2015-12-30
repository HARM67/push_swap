#include "push_swap.h"

void	init_stack(t_app *app)
{
	ft_bzero(&(app->a), sizeof(t_stack));
	ft_bzero(&(app->b), sizeof(t_stack));
	app->a.stack_nbr = 0;
	app->b.stack_nbr = 1;
	read_arg(app);
}

void	free_stack(t_app *app)
{
	t_elem *p;

	while (app->a.last)
	{
		p = app->a.last->next;
		free(app->a.last->next);
		app->a.last = p;
	}
	while (app->b.last)
	{
		p = app->b.last->next;
		free(app->b.last->next);
		app->b.last = p;
	}
}

