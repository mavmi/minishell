/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_initial.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalena <msalena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 19:29:58 by msalena           #+#    #+#             */
/*   Updated: 2021/10/26 19:29:59 by msalena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

t_par_list	*par_initial_empty_list(void)
{
	t_par_list	*new_elem;

	new_elem = (t_par_list *)malloc(sizeof(t_par_list));
	if (!new_elem)
		return (NULL);
	new_elem->size = 0;
	new_elem->begin = NULL;
	new_elem->end = NULL;
	return (new_elem);
}

/*create array of define redirects and
assign every redirect unique define number
--> return array of define redirects
	or NULL if malloc didn't allocate memory for array*/
char	**par_get_redirect(void)
{
	char	**OPER_arr;

	OPER_arr = (char **)malloc(sizeof(char *) * 8);
	if (!OPER_arr)
		return (NULL);
	OPER_arr[OPER_OUT_N] = OPER_OUT_S;
	OPER_arr[OPER_INP_N] = OPER_INP_S;
	OPER_arr[OPER_OUT_APP_N] = OPER_OUT_APP_S;
	OPER_arr[OPER_HERE_DOC_N] = OPER_HERE_DOC_S;
	OPER_arr[OPER_PIPE_N] = OPER_PIPE_S;
	OPER_arr[OPER_DOLL_N] = OPER_DOLL_S;
	OPER_arr[OPER_EQUAL_N] = OPER_EQUAL_S;
	OPER_arr[7] = NULL;
	return (OPER_arr);
}

/*create mew list's elem
--> return new list's elem
	or NULL !value (which be in new elem)
	and if malloc didn't allocate memory for new elem*/
t_par_elem	*par_get_new_elem(int type, char *value)
{
	t_par_elem	*new_elem;

	if (!value)
		return (NULL);
	new_elem = (t_par_elem *)malloc(sizeof(t_par_elem));
	if (!new_elem)
		return (NULL);
	new_elem->type = type;
	new_elem->value = ft_strdup(value);
	new_elem->prev = NULL;
	new_elem->next = NULL;
	return (new_elem);
}

/*get list elem by position
--> return position pointer of needing elem
	or NULL if !lsit or position is incorrect*/
t_par_elem	*par_get_by_pos(t_par_list *list, size_t position)
{
	size_t		i;
	t_par_elem	*removed_elem;

	if (!list || position >= list->size)
		return (NULL);
	removed_elem = list->begin;
	i = 0;
	while (i < position)
	{
		removed_elem = removed_elem->next;
		i++;
	}
	return (removed_elem);
}

/*	Initializes coun struct which keeps
	num of elem, operator size and operator flag*/
t_par_count	count_initial(void)
{
	t_par_count	coun;

	coun.size = 0;
	coun.num = DEFAULT;
	coun.i_elem = 0;
	return (coun);
}
