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
	ft_printf("\ngap  :");
	while (tmp)
	{
		ft_printf("%3d ", tmp->gap);
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

int		count_to_b(t_app *app)
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
	return (i);
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
			tmp->move_b = 1;
		tmp = tmp->next;
	}
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
	while (tmp2->generation == 0)
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

void	manual_debug(t_app *app)
{
	char	tmp[20];

	system("clear");
	make_dec(app);
	calc_stat(app);
	need_swap(app);
	what_gap(app);
	while (1)
	{
		make_dec(app);
		calc_stat(app);
		print_stacks_details(app);
		ft_bzero(tmp, 20);
		read(0, tmp, 20);
		system("clear");
		if (manual_swap(app, tmp));
		else if (manual_push(app, tmp));
		else if (manual_reverse_rotate(app, tmp));
		else if (manual_rotate(app, tmp));
		else if (ft_memcmp(tmp, "exit", 4) == 0)
			break ;
	}
}
