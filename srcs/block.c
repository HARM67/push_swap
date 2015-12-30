#include "push_swap.h"

void	identify_block(t_app *app)
{
	int i;
	int j;
	t_elem *tmp;

	i = 0;
	j = 0;
	tmp = app->pre;
	while (tmp)
	{
		if (for_block(app->statistic.data[j], app) == 0)
			i++;
		tmp->block_nbr = i;
		tmp = tmp->pre_next;
		j++;
	}
}
