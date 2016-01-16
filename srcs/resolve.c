#include "push_swap.h"

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
