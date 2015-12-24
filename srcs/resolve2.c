#include "push_swap.h"

int		need_swap_ab(t_app *app)
{
	if (app->b.first == 0 || app->b.second == 0)
		return (0);
	if (app->a.first == 0 || app->a.second == 0)
		return (0);
	if (app->a.first->nbr > app->a.second->nbr
		&& app->a.first->pre_nbr != app->nbr_nb
		&& app->a.second->pre_nbr != app->nbr_nb
		&& app->a.first->pre_nbr != 1
		&& app->a.second->pre_nbr != 1
		&& app->tmp == 2)
	{
		app->tmp = 0;
		ft_printf("ss");
		swap(&(app->a));
		swap(&(app->b));
		return (1);
	}
	return(0);
}

int		need_swap_a(t_app *app)
{
	if (app->a.first == 0 || app->a.second == 0)
		return (0);
	if (app->a.first->nbr > app->a.second->nbr
		&& app->a.first->pre_nbr != app->nbr_nb
		&& app->a.second->pre_nbr != app->nbr_nb
		&& app->a.first->pre_nbr != 1
		&& app->a.second->pre_nbr != 1)
	{
		swap(&(app->a));
		ft_printf("sa");
		return (1);
	}
	return(0);
}

int		need_swap_b(t_app *app)
{
	if (app->b.first == 0 || app->b.second == 0)
		return (0);
	if (app->tmp == 2)
	{
		app->tmp = 0;
		swap(&(app->b));
		ft_printf("sb");
		return (1);
	}
	return(0);
}

int		need_push2(t_app *app)
{
	if (app->a.first->pre_nbr != 1
			&& (app->a.first->pre_nbr == app->b.first->pre_nbr - 2
				&& app->tmp == 0)
			|| (app->a.first->pre_nbr == app->b.first->pre_nbr + 1
				&& app->tmp == 1))

	{
		if (app->a.first->pre_nbr == app->b.first->pre_nbr - 2)
			app->tmp = 1;
		if (app->a.first->pre_nbr == app->b.first->pre_nbr + 1)
			app->tmp = 2;
		push(&(app->b), &(app->a));
		ft_printf("pb");
		return (1);
	}
	return (0);
}

int		need_push(t_app *app)
{
	if (app->b.first == 0
		&& (app->a.first->pre_nbr != app->nbr_nb
			&& app->a.first->pre_nbr != app->nbr_nb - 1))
		return (0);
	if ((app->a.first->pre_nbr == app->nbr_nb && app->tmp == 0) 
			|| (app->a.first->pre_nbr == app->nbr_nb - 1
				&& app->tmp == 0)
			|| (app->a.first->pre_nbr == app->b.first->pre_nbr - 1
				&& app->tmp == 0))
	{
		if (app->a.first->pre_nbr == app->nbr_nb - 1)
			app->tmp = 1;
		push(&(app->b), &(app->a));
		ft_printf("pb");
		return (1);
	}
	return (need_push2(app));
}


