#include "push_swap.h"

int		shorter(int nb, t_app *app)
{
	if (nb > (int)app->nbr_nb / 2)
		return(nb - app->nbr_nb);
	else if (-nb > (int)app->nbr_nb / 2)
		return(nb + app->nbr_nb);
	return (nb);
}

void	fill_table(t_app *app)
{
	t_elem *tmp;
	unsigned int i;

	i = 0;
	tmp = app->pre;
	while (i < app->nbr_nb && tmp->pre_next)
	{
		app->statistic.data[i] = shorter(tmp->read_nbr - tmp->pre_next->read_nbr, app);
		i++;
		tmp = tmp->pre_next;
	}
}

void	fill_table_current(t_app *app)
{
	t_elem *tmp;
	unsigned int i;

	i = 0;
	tmp = app->pre;
	while (i < app->nbr_nb && tmp->pre_next)
	{
		if (tmp->current_nbr != -1)
			app->statistic.data[i] = shorter(tmp->current_nbr - tmp->pre_next->current_nbr, app);
		else
			app->statistic.data[i] = -2147483648;
		i++;
		tmp = tmp->pre_next;
	}
}

void	make_statistic(t_app *app)
{
	fill_table(app);
	print_table(&app->statistic, app);
}

void	make_statistic_current(t_app *app)
{
	set_stack_numbers(app);
	fill_table_current(app);
	print_table(&app->statistic, app);
}
