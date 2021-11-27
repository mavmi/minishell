/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_inter_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 17:39:13 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/11/27 19:01:13 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser_.h"

// Check if pars list valid.
// Return 1 if it is, 0 otherwise
int	pars_check_list_validity(t_pars_list *pars_list)
{
	int	opers_count;
	int	is_last_oper;

	if (!pars_list)
		return (0);
	opers_count = 0;
	is_last_oper = 0;
	while (pars_list)
	{
		is_last_oper = 0;
		if (pars_list->type != -1)
		{
			opers_count++;
			is_last_oper = 1;
		}
		else
			opers_count = 0;
		if (opers_count > 1)
			return (0);
		pars_list = pars_list->next;
	}
	if (is_last_oper)
		return (0);
	return (1);
}
