#include "push_swap.h"

void	init_stack(t_app *app)
{
	ft_bzero(&(app->a), sizeof(t_stack));
	ft_bzero(&(app->b), sizeof(t_stack));
	app->a.stack_nbr = 0;
	app->b.stack_nbr = 1;
	read_arg(app);
}
