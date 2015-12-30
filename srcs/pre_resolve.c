#include "push_swap.h"

static int		insert_elem_first(t_elem **lst, t_elem *n_elem)
{
	if (*lst == 0)
	{
		*lst = n_elem;
		return (1);
	}
	return (0);
}

static int		insert_elem_back(t_elem **lst, t_elem *n_elem)
{
	if (n_elem->nbr > (*lst)->nbr)
	{
		n_elem->pre_next = (*lst);
		*lst = n_elem;
		return (1);
	}
	return (0);
}

static int		insert_elem(t_elem *lst, t_elem *n_elem)
{
	while (lst)
	{
		if (lst->pre_next == 0)
		{
			lst->pre_next = n_elem;
			return (1);
		}
		else if (n_elem->nbr < lst->nbr && n_elem->nbr > lst->pre_next->nbr)
		{
			n_elem->pre_next = lst->pre_next;
			lst->pre_next = n_elem;
			return (1);
		}
		lst = lst->pre_next;
	}	
	return (0);
}

void			pre_nbr(t_elem *first)
{
	int i;

	i = 1;
	while (first)
	{
		first->pre_nbr = i;
		i++;
		first = first->pre_next;
	}
}

void			pre_resolve(t_app *app)
{
	t_elem *p;

	p = app->a.last;
	while (p)
	{
		if (insert_elem_first(&(app->pre), p));
		else if (insert_elem_back(&(app->pre), p));
		else if (insert_elem(app->pre, p));
		p = p->next;
	}
	pre_nbr(app->pre);
}
