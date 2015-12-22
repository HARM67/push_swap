#include "push_swap.h"

int main(int ac, char **av)
{
	t_app	*app;

	if (ac < 2)
		put_error();
	app = 0;
	init_app(&app, ac, av);
	run_app(app);
	free_app(&app);
	return (0);
}
