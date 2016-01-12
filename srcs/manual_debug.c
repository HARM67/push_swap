#include "push_swap.h"

static void	make_dec(t_app *app)
{
	int i;
	t_elem *tmp;
	t_elem *tmp2;

	tmp = app->a.last;
	while (tmp)
	{
		if (tmp->next)
			tmp2 = tmp->next;
		else
			tmp2 = app->a.last;
		i = tmp->pre_nbr - tmp2->pre_nbr;
		i = (i >= 0) ? i : i + app->nbr_nb;
		if (tmp->next)
			tmp->next->dec = i;
		else
			app->a.last->dec = i;
		tmp = tmp->next;
	}
}
void	count_to_b(t_app *app)
{
	t_elem *tmp;
	int i;

	i = 0;
	tmp = app->a.last;
	while (tmp)
	{
		if (tmp->generation != 0)
			i++;
		tmp = tmp->next;
	}
	app->nbr_to_b = i;
}

/*
void	insert_command(t_app *app, unsigned int command)
{
	t_comm *comm;

	comm = (t_comm*)ft_memalloc(sizeof(t_comm));
	if (!app->resolution)
	{
		app->resolution = comm;
		app->last_resol = comm;
	}
	else if (app->last_resol)
		app->last_resol->next = comm;
}
*/

void	last_swap(t_app *app)
{
	t_elem *tmp;

	tmp = app->a.first;
	make_costs(app);
	tmp = app->low_cost;
	go(app, tmp);
	if (app->next_cmd == 1)
	{
		swap(&app->a);
	app->nb_cmd++;
		return;
	}
}

void	recup_dans_b(t_app *app)
{
	t_elem *tmp;

	tmp = app->a.first;
	make_costs(app);
	tmp = app->low_cost;
	go(app, tmp);
	if (app->next_cmd == 1)
	{
	//	ft_printf("sa ");
		swap(&app->a);
		app->nb_cmd++;
		return;
	}
	else if (app->next_cmd == 2)
	{
	//	ft_printf("pb ");
		push(&app->b, &app->a);
	app->nb_cmd++;
	}
}

t_elem	*min_stack(t_stack *stack)
{
	int i;
	t_elem *rt;
	t_elem *tmp;

	i = 2147483647;
	tmp = stack->first;
	while (tmp)
	{
		if (i > tmp->pre_nbr)
		{
			i = tmp->pre_nbr;
			rt = tmp;
		}
		tmp = tmp->previous;
	}
	return (rt);
}

t_elem	*max_stack(t_stack *stack)
{
	int i;
	t_elem *rt;
	t_elem *tmp;

	i = 0;
	tmp = stack->first;
	while (tmp)
	{
		if (i < tmp->pre_nbr)
		{
			i = tmp->pre_nbr;
			rt = tmp;
		}
		tmp = tmp->previous;
	}
	return (rt);
}
void	come_to_start(t_app *app)
{
	t_elem move;
	t_elem *tmp;
	int i;

	tmp = app->a.first;
	i = 0;
	while (tmp->pre_nbr !=  min_stack(&app->a)->pre_nbr)
	{
		i++;
		tmp = tmp->previous;
	}
	move.distance_a = (i <= app->a.size / 2) ? i : i - app->a.size;
	i = 0;
	if (app->b.first)
	{
		tmp = app->b.first;
		while (tmp->pre_nbr !=  max_stack(&app->b)->pre_nbr)
		{
			i++;
			tmp = tmp->previous;
		}
		move.distance_b = (i <= app->b.size / 2) ? i : i - app->b.size;
	}
	else
		move.distance_b = 0;
	go(app, &move);
}


void	go_b(t_app *app)
{
	t_elem *tmp;
	t_elem *tmp2;
	t_elem move;
	int i;

	move.distance_b = 0;
	i = 0;
	tmp = app->pre;
	tmp2 = app->a.first;
	if (tmp->what_stack == 0)
		while (tmp->pre_next->what_stack == 0)
			tmp = (tmp->pre_next) ? tmp->pre_next : app->pre;
	else
		while (tmp->what_stack != 0)
			tmp = pre_previous(app, tmp);
	while (tmp2 && tmp2->pre_nbr != tmp->pre_nbr)
	{
		tmp2 = tmp2->previous;
		i++;
	}
	if (tmp2)
	{
		tmp = (tmp->pre_next) ? tmp->pre_next : app->pre;
		move.distance_a = (i <= app->a.size / 2) ? i : i - app->a.size;
	}
	else
		move.distance_a = 0;
		tmp2 = app->b.first;
	i = 0;
	while (tmp2 && tmp2->pre_nbr != tmp->pre_nbr)
	{
		tmp2 = tmp2->previous;
		i++;
	}
		move.distance_b = (i <= app->b.size / 2) ? i : i - app->b.size;
	go(app, &move);
}


void	boucle(t_app *app)
{
	int i;

	if (app->nbr_nb == 1)
		return ;
	i = 0;
	count_to_b(app);
	while (app->b.size < app->nbr_to_b)
	{
		i++;
		recup_dans_b(app);
	}
	make_dec(app);
	while (control(app) == 0)
	{
		last_swap(app);
		make_dec(app);
	}
	while (app->b.size != 0)
	{
		go_b(app);
		push(&app->a, &app->b);
		app->nb_cmd++;
	}
	come_to_start(app);
}

void	manual_debug(t_app *app)
{
	char	tmp[20];

	make_dec(app);
	calc_stat(app);
	need_swap(app);
	make_dec(app);
	make_costs(app);
	boucle(app);
	make_dec(app);
	make_costs(app);
//	print_stacks_details(app);
	print_stacks(app);
	ft_printf("en %d commandes \n", app->nb_cmd);
	return ;
	while (1)
	{
		make_dec(app);
	make_costs(app);
		ft_printf("Moin cher - %d %d", app->low_cost->nbr, app->next_cmd);
		print_stacks_details(app);
		ft_bzero(tmp, 20);
	ft_printf("%d\n", app->nb_cmd);
		read(0, tmp, 20);
		system("clear");
		if (manual_swap(app, tmp));
		else if (manual_push(app, tmp));
		else if (manual_reverse_rotate(app, tmp));
		else if (manual_rotate(app, tmp));
		else if (ft_memcmp(tmp, "g", 1) == 0)
			go_b(app);
		else if (ft_memcmp(tmp, "s", 1) == 0)
			last_swap(app);
		else if (ft_memcmp(tmp, "c", 1) == 0)
			come_to_start(app);
		else if (ft_memcmp(tmp, "n", 1) == 0)
			recup_dans_b(app);
		else if (ft_memcmp(tmp, "exit", 4) == 0)
			break ;
	}
}
