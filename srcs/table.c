#include "push_swap.h"

int		for_block(int nb, t_app *app)
{
	if (ABS(nb) < (int)(app->nbr_nb / 2 * MAX_BLOCK))
		return (1);
	return (0);
}

void	create_table(t_table *table, unsigned int size)
{
	table->data = 0;
	table->size = size - 1;
	table->data = (int*)ft_memalloc(sizeof(int) * table->size);
	if (table->data == 0)
		put_error();
}

void	print_table(t_table *table, t_app *app)
{
	unsigned int i;
	int j;

	i = 0;
	ft_printf("{BOLD}Table size : %u{EOC}\n", table->size);
	while (i < table->size)
	{
		j = 0;
		if (table->data[i] != -2147483648)
		{
			ft_printf("% 4u-%- 4u :% 4d ", i+1, i+2, table->data[i]);
			if (table->data[i] == -1)
				ft_printf("{FG_GREEN}{HIGHLIGHT}");
			else if (for_block(table->data[i], app))
				ft_printf("{FG_YELLOW}{HIGHLIGHT}");
			else
				ft_printf("{FG_RED}{HIGHLIGHT}");
			while (j < ABS(table->data[i]))
			{
				ft_printf(" ");
				j++;
			}
				ft_printf("{EOC}");
			ft_printf("\n");
		}
		i++;
	}
}
