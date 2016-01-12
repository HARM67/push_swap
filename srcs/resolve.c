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

	i = app->nbr_nb;
	if (i == 1)
		return (1);
	rt = 0;
	p = app->a.last;
	while (p)
	{
		rt += p->dec;
		p = p->next;
	}
	if (i == rt)
		return ((app->a.last->pre_nbr == i) ? 1 : 2);
	return (0);
}

void	resolve2(t_app *app)
{
	while (app->b.first)
	{
		if (app->temoin && !app->debug)
			ft_printf(" ");
		push(&(app->a), &(app->b));
		ft_printf("pa");
		if (app->debug == 1)
			print_stacks(app);
		app->temoin = 1;
	}
	ft_printf("\n");
}

void	resolve(t_app *app)
{
	void (*f_p)(t_stack *);

	f_p = (calculate_rot(app) > 0) ? reverse_rotate : rotate;
	if (app->debug == 1)
		print_stacks(app);
	while (!control(app))
	{
		if (app->temoin && !app->debug)
			ft_printf(" ");
		if (need_swap_ab(app));
		else if (need_swap_a(app));
		else if (need_swap_b(app));
		else if (need_push(app));
		else
		{
			(f_p == rotate) ? ft_printf("ra"): ft_printf("rra");
			f_p(&(app->a));
		}
		if (app->debug == 1)
			print_stacks(app);
			app->temoin = 1;
	}
	resolve2(app);
}
