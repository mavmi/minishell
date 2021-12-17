/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_list_checker.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 17:12:55 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/12/16 19:11:09 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

int	par_check_list(t_par_list *list)
{
	int			opers_in_row;
	t_par_elem	*elem;

	if (!list || !list->size || !list->begin || !list->end
		|| list->begin->type == OPER_PIPE_N
		|| (list->end->type != DEFAULT_N && list->end->type != OPER_DOLL_N))
		return (0);
	elem = list->begin;
	opers_in_row = 0;
	while (elem)
	{
		if (elem->type == OPER_PIPE_N && elem->next->type == OPER_PIPE_N)
			return (0);
		if (elem->type != DEFAULT_N && elem->type != OPER_DOLL_N
			&& elem->type != OPER_PIPE_N)
			opers_in_row++;
		else
			opers_in_row = 0;
		if (opers_in_row > 1 || (opers_in_row && !elem->next))
			return (0);
		elem = elem->next;
	}
	return (1);
}
