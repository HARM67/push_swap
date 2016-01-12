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
unsigned int	stack_size(t_stack *stack)
{
	unsigned int i;
	t_elem *tmp;

	i = 0;
	tmp = stack->last;
	if (!tmp)
		return (0);
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

int	go(t_app *app, t_elem *elem)
{
	while (elem->distance_a > 0 || elem->distance_b > 0)
	{
		if (elem->distance_b > 0 && elem->distance_a > 0)
		{
	//		ft_printf("rr ");
			rotate(&app->a);
			rotate(&app->b);
			elem->distance_a--;
			elem->distance_b--;
			app->nb_cmd++;
		}
		else if (elem->distance_a > 0)
		{
	//		ft_printf("ra ");
			rotate(&app->a);
			elem->distance_a--;
			app->nb_cmd++;
		}
		else if (elem->distance_b > 0)
		{
	//		ft_printf("rb ");
			rotate(&app->b);
			elem->distance_b--;
			app->nb_cmd++;
		}
	}
	while (elem->distance_a < 0 || elem->distance_b < 0)
	{
		if (elem->distance_b < 0 && elem->distance_a < 0)
		{
	//		ft_printf("rrr ");
			reverse_rotate(&app->a);
			reverse_rotate(&app->b);
			elem->distance_a++;
			elem->distance_b++;
			app->nb_cmd++;
		}
		else if (elem->distance_a < 0)
		{
	//		ft_printf("rra ");
			reverse_rotate(&app->a);
			elem->distance_a++;
			app->nb_cmd++;
		}
		else if (elem->distance_b < 0)
		{
	//		ft_printf("rrb ");
			reverse_rotate(&app->b);
			elem->distance_b++;
			app->nb_cmd++;
		}
	}
	return (0);
}

int	good_in_b(t_app *app, t_elem *elem, t_elem *position)
{
	t_elem *tmp;
	t_elem *tmp2;

	tmp = position;
	tmp2 = previous(app, tmp);
	if (tmp == tmp2)
		return (1);
	while (tmp != tmp2)
	{
		if (elem->pre_nbr == tmp->pre_nbr)
			return (1);
		tmp = (tmp->pre_next) ? tmp->pre_next : app->pre;
	}
	return (0);
}

t_elem	*next_push_b(t_app *app)
{
	int rb;
	t_elem *tmp;
	t_elem *tmp2;

	rb = 0;
	tmp = app->a.first;
	while (tmp != app->a.last)
	{
		if (tmp->move_b)
		{
			if (tmp->need_swap == 0 ||
					(tmp->need_swap == 1 && previous(app, tmp)->move_b == 0))
				return (tmp);
			else if (tmp->need_swap == 1 && previous(app, tmp)->move_b)
				return (previous(app, tmp));
		}
		tmp = previous(app, tmp);
	}
	return (tmp);
}

int		dest_b(t_app *app, t_elem *tmp)
{
	t_elem *tmp2;
	int dest;
	int s_b;

	dest = 0;
	tmp2 = app->b.last;
	while (tmp2 && !good_in_b(app, tmp, tmp2))
	{
		tmp2 = previous(app, tmp2);
		dest++;
	}
	s_b = stack_size(&app->b);
	if (dest > s_b / 2)
		dest -= s_b;
	return (dest);
}

void	make_cost(t_elem *elem)
{
	if (elem->distance_a > 0 && elem->distance_b > 0)
		elem->cost = (elem->distance_a > elem->distance_b) ?
			elem->distance_a : elem->distance_b;
	else if (elem->distance_a < 0 && elem->distance_b < 0)
		elem->cost = (elem->distance_a < elem->distance_b) ?
			-elem->distance_a: -elem->distance_b;
	else
		elem->cost = ABS(elem->distance_a) + ABS( elem->distance_b);
}

void	normalize_cost(t_app *app, t_elem *elem)
{
	int a_size;
	int b_size;

	a_size = stack_size(&app->a);
	b_size = stack_size(&app->b);
	if (elem->distance_a > a_size / 2)
		elem->distance_a -= a_size;
}

void	make_costs(t_app *app)
{
	int i;
	t_elem *tmp;
	int size;
	int low;

	size = stack_size(&app->a);
	low = 2147483647;
	tmp = app->a.first;
	i = 0;
	app->next_cmd = 0;
	if (size == 1)
	{
		app->low_cost = tmp;
		return ;
	}
	while (i < size)
	{
			tmp->distance_a = (i <= size / 2) ? i : i - size;
			tmp->distance_b = dest_b(app, tmp);
			make_cost(tmp);
			normalize_cost(app, tmp);
			if (ABS(tmp->distance_a) < low && tmp->need_swap && previous(app, tmp)->need_swap == 2)
			{
				low = ABS(tmp->distance_a);
				app->low_cost = tmp;
				tmp->distance_b = 0;
				app->next_cmd = 1;
			}
			if (tmp->cost < low && tmp->move_b && tmp->need_swap == 0 && 
					previous(app, tmp)->need_swap == 0)
			{
				low = tmp->cost;
				app->low_cost = tmp;
				app->next_cmd = 2;
			}
		tmp = previous(app, tmp);
		i++;
	}
}

void	last_swap(t_app *app)
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
	int s_a;
	int s_b;
	t_elem *tmp;
	int i;

	s_a = stack_size(&app->a);
	s_b = stack_size(&app->b);
	tmp = app->a.first;
	i = 0;
	while (tmp->pre_nbr !=  min_stack(&app->a)->pre_nbr)
	{
		i++;
		tmp = tmp->previous;
	}
	move.distance_a = (i <= s_a / 2) ? i : i - s_a;
	i = 0;
	if (app->b.first)
	{
		tmp = app->b.first;
		while (tmp->pre_nbr !=  max_stack(&app->b)->pre_nbr)
		{
			i++;
			tmp = tmp->previous;
		}
		move.distance_b = (i <= s_b / 2) ? i : i - s_b;
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
	int s_a;
	int s_b;
	int i;

	s_a = stack_size(&app->a);
	s_b = stack_size(&app->b);
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
		move.distance_a = (i <= s_a / 2) ? i : i - s_a;
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
		move.distance_b = (i <= s_b / 2) ? i : i - s_b;
	go(app, &move);
}


void	boucle(t_app *app)
{
	int i;

	i = 0;
	count_to_b(app);
	while (stack_size(&app->b) < app->nbr_to_b)
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
	while (stack_size(&app->b) != 0)
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
	boucle(app);
	make_dec(app);
	print_stacks_details(app);
	//print_stacks(app);
	ft_printf("en %d commandes \n", app->nb_cmd);
	return ;
	while (1)
	{
		make_dec(app);
		print_stacks_details(app);
		ft_bzero(tmp, 20);
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
