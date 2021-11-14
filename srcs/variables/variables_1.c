/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 12:41:39 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/11/14 13:04:53 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/variables.h"

// Create new variable element.
// May return NULL
t_var	*var_get_new_elem(char *name, char *value)
{
	t_var	*elem;

	if (!name || !value)
		return (NULL);
	elem = (t_var *)malloc(sizeof(t_var));
	if (!elem)
		return (NULL);
	elem->name = ft_strdup(name);
	elem->value = ft_strdup(value);
	elem->next = NULL;
	if (!elem->name || !elem->value)
	{
		var_destroy_elem(elem);
		return (NULL);
	}
	return (elem);
}

void	var_destroy_elem(t_var *elem)
{
	if (!elem)
		return (NULL);
	free(elem->name);
	free(elem->value);
	free(elem);
}

void	var_push_back(t_var *list, t_var *elem)
{	
	if (!list || !elem)
		return ;
	while (list->next)
		list = list->next;
	list->next = elem;
}

void	var_destroy_list(t_var *list)
{
	t_var	*ptr;
	t_var	*next;

	if (!list)
		return ;
	ptr = list;
	while (ptr)
	{
		next = ptr->next;
		var_destroy_elem(ptr);
		ptr = next;
	}
}
