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
		tmp->dec = i;
		tmp = tmp->next;
	}
}

void	calculate_gene(t_app*app)
{
	int i;
	t_elem *tmp;

	i = 0;
	tmp = app->a.last;
	while (tmp)
	{
		i += tmp->dec;
		tmp = tmp->next;
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
	s->gain = (ancien - nouveau) / (int)app->nbr_nb;
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

void	manual_debug(t_app *app)
{
	char	tmp[20];

	system("clear");
	while (1)
	{
		make_dec(app);
		calculate_gene(app);
		make_gains(app);
		ft_printf("There is %d generation\n", app->gene_nb);
		print_stacks_details(app);
		ft_bzero(tmp, 20);
		read(0, tmp, 20);
		system("clear");
		if (manual_swap(app, tmp));
		else if (manual_push(app, tmp));
		else if (manual_reverse_rotate(app, tmp));
		else if (manual_rotate(app, tmp));
		/*/else if (ft_memcmp(tmp, "stat origin", 11) == 0)
			make_statistic(app);
		else if (ft_memcmp(tmp, "set block", 9) == 0)
			identify_block(app);
		*/else if (ft_memcmp(tmp, "exit", 4) == 0)
			break ;
	}
}

