/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 16:10:43 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/11/21 13:26:45 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser_.h"

// Create new t_pars_list elem.
// May return NULL
t_pars_list	*pars_get_new_elem(int type, char *value)
{
	t_pars_list	*elem;	

	if (!value)
		return (NULL);
	elem = (t_pars_list *)malloc(sizeof(t_pars_list));
	if (!elem)
		return (NULL);
	elem->next = NULL;
	elem->type = type;
	elem->value = ft_strdup(value);
	if (!elem->value)
	{
		free(elem);
		return (NULL);
	}
	return (elem);
}

void	pars_push_back(t_pars_list *list, t_pars_list *elem)
{
	t_pars_list	*ptr;

	if (!elem)
		return ;
	ptr = list;
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = elem;
}

void	pars_destroy_elem(t_pars_list *elem)
{
	if (!elem)
		return ;
	free(elem->value);
	free(elem);
}

void	pars_destroy_list(t_pars_list *list)
{
	t_pars_list	*ptr;
	t_pars_list	*next;

	if (!list)
		return ;
	ptr = list;
	while (ptr)
	{
		next = ptr->next;
		pars_destroy_elem(ptr);
		ptr = next;
	}
}
