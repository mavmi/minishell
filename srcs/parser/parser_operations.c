/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalena <msalena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 19:29:55 by msalena           #+#    #+#             */
/*   Updated: 2021/10/26 19:29:56 by msalena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

/*put new elem at the end of list
--> return 1 if everyfing good
	and 0 if input argums didn't come*/
int	par_push_back(t_par_elem *new_back, t_par_list *list)
{
	if (!new_back || !list)
		return (0);
	if (list->begin != NULL)
	{
		list->end->next = new_back;
		new_back->prev = list->end;
		list->end = new_back;
	}
	else
	{
		list->begin = new_back;
		list->end = new_back;
	}
	list->size++;
	return (1);
}

static void	par_rem_conditions(t_par_list *list, t_par_elem *elem)
{
	if (list->size == 1)
	{
		list->begin = NULL;
		list->end = NULL;
	}
	else if (elem == list->begin)
	{
		elem->next->prev = NULL;
		list->begin = elem->next;
	}
	else if (elem == list->end)
	{
		elem->prev->next = NULL;
		list->end = elem->prev;
	}
	else
	{
		elem->prev->next = elem->next;
		elem->next->prev = elem->prev;
	}
}

/*remove elem by position*/
void	par_remove_by_pos(t_par_list *list, size_t position)
{
	t_par_elem	*removed_elem;

	if (!list || position >= list->size)
		return ;
	removed_elem = par_get_by_pos(list, position);
	if (!removed_elem)
		return ;
	par_rem_conditions(list, removed_elem);
	par_destroy_elem(removed_elem);
	list->size--;
}

/*free list'elems*/
void	par_destroy_elem(t_par_elem *elem)
{
	free(elem->value);
	free(elem);
}

/*destroy all list's elems and list too*/
void	par_destroy_all(t_par_list *list)
{
	t_par_elem	*elem;
	t_par_elem	*tmp;

	if (!list)
		return ;
	if (!list->begin && !list->end)
	{
		free(list);
		return ;
	}
	elem = list->begin;
	tmp = NULL;
	list->begin = NULL;
	list->end = NULL;
	while (elem->next)
	{
		tmp = elem->next;
		par_destroy_elem(elem);
		elem = tmp;
	}
	par_destroy_elem(elem);
	free (list);
}
