/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 13:02:49 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/11/14 13:03:13 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/variables.h"

// Find variable with specified name
// in the list.
// May return NULL
t_var	*var_get(t_var *list, char *name)
{
	if (!list || !name)
		return (NULL);
	while (list)
	{
		if (utils_cmp_strings(list->name, name))
			return (list);
		list = list->next;
	}
	return (NULL);
}

void	var_remove(t_var **list, char *name)
{
	t_var	*prev;
	t_var	*ptr;

	if (!list || !(*list) || !name)
		return ;
	prev = NULL;
	ptr = *list;
	while (ptr)
	{
		if (utils_cmp_strings(ptr->name, name))
		{
			if (prev)
				prev->next = ptr->next;
			else
				*list = ptr->next;
			var_destroy_elem(ptr);
			return ;
		}
		prev = ptr;
		ptr = ptr->next;
	}
}
