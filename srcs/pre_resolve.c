#include "push_swap.h"

static int		insert_elem_first(t_elem **lst, t_elem *n_elem, t_elem **lst2)
{
	if (*lst == 0)
	{
		*lst2 = n_elem;
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
		(*lst)->pre_previous = n_elem;
		*lst = n_elem;
		return (1);
	}
	return (0);
}

static int		insert_elem(t_elem *lst, t_elem *n_elem, t_elem **lst2)
{
	while (lst)
	{
		if (lst->pre_next == 0)
		{
			n_elem->pre_previous = lst;
			lst->pre_next = n_elem;
			*lst2 = n_elem;
			return (1);
		}
		else if (n_elem->nbr < lst->nbr && n_elem->nbr > lst->pre_next->nbr)
		{
			n_elem->pre_next = lst->pre_next;
			lst->pre_next = n_elem;
			n_elem->pre_previous = lst;
			n_elem->pre_next->pre_previous = n_elem;
			return (1);
		}
		lst = lst->pre_next;
	}	
	return (0);
}

void			pre_nbr(t_elem *first, t_app *app)
{
	int i;

	i = app->nbr_nb;
	while (first)
	{
		first->pre_nbr = i;
		i--;
		first = first->pre_next;
	}
}

void			pre_resolve(t_app *app)
{
	t_elem *p;

	p = app->a.last;
	while (p)
	{
		if (insert_elem_first(&(app->pre), p, &(app->pre_last)));
		else if (insert_elem_back(&(app->pre), p));
		else
			insert_elem(app->pre, p, &(app->pre_last));
		p = p->next;
	}
	pre_nbr(app->pre, app);
}
