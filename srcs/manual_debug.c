#include "push_swap.h"


static	void	print_stack_details(t_stack *stack, t_app *app)
{
	t_elem *tmp;

	tmp = stack->last;
	if (control(app) == 1)
		ft_printf("{FG_GREEN}{DARK}");
	else if (control(app) == 2)
		ft_printf("{FG_YELLOW}");
	else 
		ft_printf("{FG_RED}");
	while (tmp)
	{
		if (tmp->change)
			ft_printf("{HIGHLIGHT}");
		ft_printf("%3d ", tmp->nbr);
		tmp->change = 0;
		tmp = tmp->next;
	}
	tmp = stack->last;
	ft_printf("{EOC}{FG_BLUE}");
	ft_printf("\npre  :");
	while (tmp)
	{
		ft_printf("%3d ", tmp->pre_nbr);
		tmp = tmp->next;
	}
	tmp = stack->last;
	ft_printf("\ndec  :");
	while (tmp)
	{
		ft_printf("%3d ", tmp->dec);
		tmp = tmp->next;
	}
	tmp = stack->last;
	ft_printf("\ngain :");
	while (tmp)
	{
		ft_printf("%3d ", tmp->gain);
		tmp = tmp->next;
	}
	tmp = stack->last;
	ft_printf("\ngene :");
	while (tmp)
	{
		ft_printf("%3d ", tmp->generation);
		tmp = tmp->next;
	}
	tmp = stack->last;
	ft_printf("\nzoneS:");
	while (tmp)
	{
		ft_printf("%3d ", tmp->zone_size);
		tmp = tmp->next;
	}
	tmp = stack->last;
	ft_printf("\nNswap:");
	while (tmp)
	{
		ft_printf("%3d ", tmp->need_swap);
		tmp = tmp->next;
	}
	tmp = stack->last;
	ft_printf("\nmoveB:");
	while (tmp)
	{
		ft_printf("%3d ", tmp->move_b);
		tmp = tmp->next;
	}
	tmp = stack->last;
	ft_printf("\nstack:");
	while (tmp)
	{
		ft_printf("%3d ", tmp->what_stack);
		tmp = tmp->next;
	}
	tmp = stack->last;
	ft_printf("\ngap  :");
	while (tmp)
	{
		ft_printf("%3d ", tmp->gap);
		tmp = tmp->next;
	}
	tmp = stack->last;
	ft_printf("\ndistA:");
	while (tmp)
	{
		ft_printf("%3d ", tmp->distance_a);
		tmp = tmp->next;
	}
	tmp = stack->last;
	ft_printf("\ndistB:");
	while (tmp)
	{
		ft_printf("%3d ", tmp->distance_b);
		tmp = tmp->next;
	}
	tmp = stack->last;
	ft_printf("\ncost :");
	while (tmp)
	{
		ft_printf("%3d ", tmp->cost);
		tmp = tmp->next;
	}
	ft_printf("{EOC}");
}

static void		print_stacks_details(t_app *app)
{
	ft_printf("{FG_BLUE}");
	ft_printf("\n{BOLD}a    :{EOC}");
	print_stack_details(&(app->a), app);
	ft_printf("{FG_BLUE}");
	ft_printf("\n{BOLD}b    :{EOC}");
	print_stack_details(&(app->b), app);
	if (app->color)
		ft_printf("{EOC}");
	ft_printf("\n\n");
}

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

void	zone_size(t_app *app, t_elem *tmp)
{
	int i;
	int j;
	t_elem *tmp2;

	tmp2 = tmp;
	i = 0;
	j = 0;
	while (i < app->nbr_nb)
	{
		i += tmp2->dec;
		j++;
		tmp2 = (tmp2->next) ? tmp2->next : app->a.last;
	}
	tmp = (tmp->previous) ? tmp->previous : app->a.first;
	tmp->zone_size = j;
}

void	zones_size(t_app *app)
{
	t_elem *tmp;

	tmp = app->a.last;
	while (tmp)
	{
		zone_size(app, tmp);
		tmp = tmp->next;
	}
}

void	select_zone(t_app *app)
{
	t_elem	*tmp;
	t_elem *tmp2;
	int	zone;

	zone = 0;
	tmp = app->a.last;
	tmp2 = tmp;
	while (tmp)
	{
		if (tmp2->zone_size < tmp->zone_size ||(
				tmp2->zone_size == tmp->zone_size &&
				tmp2->pre_nbr > tmp->pre_nbr))
			tmp2 = tmp;
		tmp = tmp->next;
	}
	app->zone_select = tmp2;
}

void	calculate_gene(t_app *app)
{
	int i;
	t_elem *tmp;
	t_elem *tmp2;

	i = 0;
	tmp = app->zone_select;
	tmp2 = tmp;
	while (1)
	{
		tmp->generation = i / app->nbr_nb;
		tmp = (tmp->next) ? tmp->next : app->a.last;
		i += tmp->dec;
		if (tmp == tmp2)
			break;
	}
	app->gene_nb = i / app->nbr_nb;
}

static void	make_gain(t_app *app, t_elem *tmp)
{
	t_elem *p;
	t_elem *s;
	int ancien;
	int nouveau;

	p = (tmp->previous) ? tmp->previous : app->a.first;
	s = (tmp->next) ? tmp->next : app->a.last;
	ancien = p->dec + tmp->dec + s->dec;
	nouveau = app->nbr_nb - tmp->dec;
	nouveau += (p->dec + tmp->dec) % app->nbr_nb;
	nouveau += (s->dec + tmp->dec) % app->nbr_nb;
	tmp->gain = (ancien - nouveau) / (int)app->nbr_nb;
}

static void	make_gains(t_app *app)
{
	t_elem *tmp;

	tmp = app->a.last;
	while (tmp)
	{
		make_gain(app, tmp);
		tmp = tmp->next;
	}
}

void	try_swap(t_app *app, t_elem *tmp)
{
	t_elem *p;
	t_elem *s;
	int p_new;
	int	a_new;
	int s_new;

	p = (tmp->previous) ? tmp->previous : app->a.first;
	s = (tmp->next) ? tmp->next : app->a.last;

	a_new = app->nbr_nb - tmp->dec;
	p_new = (p->dec + tmp->dec) % app->nbr_nb;
	s_new = (s->dec + tmp->dec) % app->nbr_nb;
	p->dec = p_new;
	s->dec = s_new;
	tmp->dec = a_new;
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

void print(t_app *app)
{
	int i;

	i = 0;
	while (i < app->nbr_nb)
	{
		ft_printf("%d\n", app->swap_comb[i]);
		i++;
	}
	ft_printf("%d\n", app->best);
}

void	calc_stat(t_app *app)
{
			zones_size(app);
			select_zone(app);
			calculate_gene(app);
			make_gains(app);
}

void	to_move_b(t_app *app)
{
	t_elem *tmp;

	tmp = app->a.last;
	while (tmp)
	{
		if (tmp->generation != 0)
		{
			app->nbr_to_b++;
			tmp->move_b = 1;
		}
		tmp = tmp->next;
	}
}

t_elem	*next(t_app *app, t_elem *elem)
{
	if (elem->next)
		return (elem->next);
	if (elem->what_stack)
		return (app->b.last);
	return (app->a.last);
}
t_elem	*previous(t_app *app, t_elem *elem)
{
	if (elem->previous)
		return (elem->previous);
	if (elem->what_stack)
		return (app->b.first);
	return (app->a.first);
}

int		need_swap(t_app *app)
{
	t_elem *tmp;
	t_elem *tmp2;
	int i;

	i = 0;
	tmp2 = app->a.first;
	tmp = tmp2;
	while (1)
	{
		if (tmp2->gain == 1)
		{
			tmp2->need_swap = 1;
			(previous(app, tmp2))->need_swap = 2;
			app->swap_comb[i] = tmp2->pre_nbr;
			try_swap(app, tmp2);
			calc_stat(app);
			i++;
		}
		tmp2 = (tmp2->previous) ? tmp2->previous : app->a.first;
		if (tmp == tmp2)
			break ;
	}
	to_move_b(app);
	return (0);
}

void	what_gap(t_app *app)
{
	t_elem *tmp;
	t_elem *tmp2;
	int i;
	int j;

	i = 0;
	j = 1;
	tmp2 = app->zone_select;
	while (tmp2->generation == 0 && i < app->nbr_nb)
	{
		tmp2 = (tmp2->pre_next) ? tmp2->pre_next : app->pre;
		i++;
	}
	while (i < app->nbr_nb)
	{
		if (tmp2->generation == 0)
		{
			j++;
			while (tmp2->generation == 0)
			{
				tmp2 = (tmp2->pre_next) ? tmp2->pre_next : app->pre;
				i++;
			}
		}
		else
		{
			tmp2->gap = j;
		ft_printf("%d\n", tmp2->pre_nbr);
			tmp2 = (tmp2->pre_next) ? tmp2->pre_next : app->pre;
			i++;
		}
	}
	to_move_b(app);
}

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
			ft_printf("rr ");
			rotate(&app->a);
			rotate(&app->b);
			elem->distance_a--;
			elem->distance_b--;
			app->nb_cmd++;
		}
		else if (elem->distance_a > 0)
		{
			ft_printf("ra ");
			rotate(&app->a);
			elem->distance_a--;
			app->nb_cmd++;
		}
		else if (elem->distance_b > 0)
		{
			ft_printf("rb ");
			rotate(&app->b);
			elem->distance_b--;
			app->nb_cmd++;
		}
	}
	while (elem->distance_a < 0 || elem->distance_b < 0)
	{
		if (elem->distance_b < 0 && elem->distance_a < 0)
		{
			ft_printf("rrr ");
			reverse_rotate(&app->a);
			reverse_rotate(&app->b);
			elem->distance_a++;
			elem->distance_b++;
			app->nb_cmd++;
		}
		else if (elem->distance_a < 0)
		{
			ft_printf("rra ");
			reverse_rotate(&app->a);
			elem->distance_a++;
			app->nb_cmd++;
		}
		else if (elem->distance_b < 0)
		{
			ft_printf("rrb ");
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
			if (i < low && tmp->need_swap && previous(app, tmp)->need_swap == 2)
			{
				low = i;
				app->low_cost = tmp;
				tmp->distance_b = 0;
				app->next_cmd = 1;
			}
			if (tmp->cost < low && tmp->move_b && tmp->need_swap != 2)
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
		ft_printf("sa ");
		swap(&app->a);
		return;
	}
	app->nb_cmd++;
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
		ft_printf("sa ");
		swap(&app->a);
		return;
	}
	else if (app->next_cmd == 2)
	{
		ft_printf("pb ");
		push(&app->b, &app->a);
	}
	app->nb_cmd++;
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

int		dest_a(t_app *app, t_elem *tmp)
{
	t_elem *tmp2;
	int dest;
	int s_b;

	dest = 0;
	tmp2 = app->a.first;
	while (tmp2 && !good_in_b(app, tmp, next(app, tmp2)))
	{
		tmp2 = previous(app, tmp2);
		dest++;
	}
	s_b = stack_size(&app->a);
	if (dest > s_b / 2)
		dest -= s_b;
	return (dest);
}

void	make_costs_2(t_app *app)
{
	int i;
	t_elem *tmp;
	int size;
	int low;

	size = stack_size(&app->b);
	low = 2147483647;
	tmp = app->b.first;
	i = 0;
	app->next_cmd = 0;
	if (size == 1)
	{
		app->low_cost = tmp;
		return ;
	}
	while (i < size)
	{
			tmp->distance_b = (i <= size / 2) ? i : i - size;
			tmp->distance_a = dest_a(app, tmp);
			make_cost(tmp);
			normalize_cost(app, tmp);
			if (tmp->cost < low)
			{
				low = tmp->cost;
				app->low_cost = tmp;
				app->next_cmd = 3;
			}
		tmp = previous(app, tmp);
		i++;
	}
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
	while (tmp->pre_next->what_stack == 0)
		tmp = (tmp->pre_next) ? tmp->pre_next : app->pre;
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

void	recup_dans_a(t_app *app)
{
	go_b(app);
	ft_printf("pa ");
	push(&app->a, &app->b);
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
	print_stacks(app);
	}
	make_dec(app);
	while (control(app) == 0)
	{
		last_swap(app);
		make_dec(app);
	print_stacks(app);
	}
	
	while (stack_size(&app->b) != 0)
	{
		recup_dans_a(app);
	print_stacks(app);
	}
	come_to_start(app);
}

void	manual_debug(t_app *app)
{
	char	tmp[20];

	system("clear");
	make_dec(app);
	calc_stat(app);
	need_swap(app);
	//what_gap(app);
	//make_costs(app);
	//print_stacks_details(app);
	print_stacks(app);
	boucle(app);
	while (1)
	{
		make_dec(app);
	//	calc_stat(app);
	//	make_costs(app);
		print_stacks_details(app);
//	print_stacks(app);
	ft_printf("nbr %d\n", app->nb_cmd);
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
		else if (ft_memcmp(tmp, "a", 1) == 0)
			recup_dans_a(app);
		else if (ft_memcmp(tmp, "c", 1) == 0)
			come_to_start(app);
		else if (ft_memcmp(tmp, "n", 1) == 0)
			recup_dans_b(app);
		else if (ft_memcmp(tmp, "exit", 4) == 0)
			break ;
	}
}
