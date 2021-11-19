/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_work_with_mallocs.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalena <msalena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 17:53:40 by msalena           #+#    #+#             */
/*   Updated: 2021/11/14 17:53:41 by msalena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

t_par_list	*par_free_out(char **oper_arr, t_par_list *list)
{
	if (!oper_arr && !list)
		return (NULL);
	if (!oper_arr)
		par_destroy_all(list);
	else if (!list)
		free(oper_arr);
	else
	{
		free(oper_arr);
		par_destroy_all(list);
	}
	return (NULL);
}

char	*par_check_on_slash(char *str, int *str_c, char *ret_str)
{
	if (!str || !ret_str)
		return (NULL);
	if (str[*str_c] == '\\')
	{
		free(ret_str);
		return (NULL);
	}
	return (str);
}

char	*par_check_malloc(char *str)
{
	char	*return_str;

	if (!str)
		return (NULL);
	return_str = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!return_str)
		return (NULL);
	return (return_str);
}
