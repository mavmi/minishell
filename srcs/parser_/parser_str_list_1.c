/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_str_list_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 12:58:53 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/11/20 13:26:26 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser_.h"

// Create new element of strings list.
// May return NULL
t_strings	*pars_get_new_str_elem(char *str)
{
	t_strings	*elem;

	if (!str)
		return (NULL);
	elem = (t_strings *)malloc(sizeof(t_strings));
	if (!elem)
		return (NULL);
	elem->string = ft_strdup(str);
	elem->next = NULL;
	if (!elem->string)
	{
		free(elem);
		return (NULL);
	}
	return (elem);
}

void	pars_destroy_str_elem(t_strings *elem)
{
	if (!elem)
		return ;
	free(elem->string);
	free(elem);
}

void	pars_destroy_str_list(t_strings *list)
{
	t_strings	*ptr;
	t_strings	*next;

	if (!list)
		return ;
	ptr = list;
	while (ptr)
	{
		next = ptr->next;
		pars_destroy_str_elem(ptr);
		ptr = next;		
	}
}

void	pars_push_back_str(t_strings *list, t_strings *elem)
{
	if (!list || !elem)
		return ;
	while (list->next)
	{
		list = list->next;
	}
	list->next = elem;
}
