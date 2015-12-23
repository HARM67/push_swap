#include "push_swap.h"

int calculate_rot(t_app *app)
{
	int i;
	t_elem *p;

	i = 0;
	p = app->a.last;
	while (p && p->pre_nbr != 1)
	{
		p = p->next;
		i++;
	}
	if (i > app->nbr_nb / 2 )
		i -= app->nbr_nb;
	return (i);
}

int		control(t_app *app)
{
	int		i;
	t_elem	*p;
	int rt;

	i = 1;
	rt = 1;
	p = app->a.last;
	while (p)
	{
		if (i != p->pre_nbr)
			return (0);
		p = p->next;
		i++;
	}
	i = app->nbr_nb;
	p = app->b.last;
	while (p)
	{
		rt = 2;
		if (i != p->pre_nbr)
			return (0);
		p = p->next;
		i--;
	}
	return (rt);
}

int		need_swap_ab(t_app *app)
{
	if (app->b.first == 0 || app->b.second == 0)
		return (0);
	if (app->a.first->nbr > app->a.second->nbr
		&& app->a.first->pre_nbr != app->nbr_nb
		&& app->a.second->pre_nbr != app->nbr_nb
		&& app->tmp == 2)
	{
		app->tmp == 0;
		ft_printf("ss ");
		swap(&(app->a));
		swap(&(app->b));
		return (1);
	}
	return(0);
}

int		need_swap_a(t_app *app)
{
	if (app->a.first->nbr > app->a.second->nbr
		&& app->a.first->pre_nbr != app->nbr_nb
		&& app->a.second->pre_nbr != app->nbr_nb)
	{
		swap(&(app->a));
		ft_printf("sa ");
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
		ft_printf("sb ");
		return (1);
	}
	return(0);
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
		ft_printf("pb ");
		return (1);
	}
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
		ft_printf("pb ");
		return (1);
	}
	return (0);
}

void	resolve(t_app *app)
{
	int i = 0;
	void (*f_p)(t_stack *);

	f_p = (calculate_rot(app) > 0) ? reverse_rotate : rotate;
	while (!control(app))
	{
		if (need_swap_ab(app));
		else if (need_swap_a(app));
		else if (need_swap_b(app));
		else if (need_push(app));
		else
			f_p(&(app->a));
		i++;
	}
	while (app->b.first)
	{
		push(&(app->a), &(app->b));
		ft_printf("pa ");
	}
	ft_printf("\n");
}
