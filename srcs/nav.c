/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nav.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <mfroehly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 16:11:25 by mfroehly          #+#    #+#             */
/*   Updated: 2016/01/12 16:28:29 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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

t_elem	*pre_previous(t_app *app, t_elem *elem)
{
	if (elem->pre_previous)
		return (elem->pre_previous);
	return (app->pre_last);
}

t_elem	*pre_next(t_app *app, t_elem *elem)
{
	if (elem->pre_next)
		return (elem->pre_next);
	return (app->pre);
}
