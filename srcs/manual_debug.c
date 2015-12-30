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
	ft_printf("\nstart:");
	while (tmp)
	{
		ft_printf("%3d ", tmp->read_nbr);
		tmp = tmp->next;
	}
	tmp = stack->last;
	ft_printf("\nblock:");
	while (tmp)
	{
		ft_printf("%3d ", tmp->block_nbr);
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

void	manual_debug(t_app *app)
{
	char	tmp[20];

	system("clear");
	while (1)
	{
		make_statistic_current(app);
		print_stacks_details(app);
		ft_bzero(tmp, 20);
		read(0, tmp, 20);
		system("clear");
		if (manual_swap(app, tmp));
		else if (manual_push(app, tmp));
		else if (manual_reverse_rotate(app, tmp));
		else if (manual_rotate(app, tmp));
		else if (ft_memcmp(tmp, "stat origin", 11) == 0)
			make_statistic(app);
		else if (ft_memcmp(tmp, "set block", 9) == 0)
			identify_block(app);
		else if (ft_memcmp(tmp, "exit", 4) == 0)
			break ;
	}
}
