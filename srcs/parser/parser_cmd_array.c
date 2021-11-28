/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd_array.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalena <msalena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 17:51:02 by msalena           #+#    #+#             */
/*   Updated: 2021/11/28 16:46:03 by msalena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

static char	**arr_add_realloc(char *added_str, char **arr_str)
{
	char	**new_arr;
	int		tmp_i;

	tmp_i = 0;
	while (arr_str && arr_str[tmp_i])
	{
		tmp_i++;
	}
	new_arr = (char **)malloc(sizeof(char *) * (tmp_i + 2));
	if (!new_arr)
		return (NULL);
	tmp_i = 0;
	while (arr_str && arr_str[tmp_i])
	{
		new_arr[tmp_i] = arr_str[tmp_i];
		tmp_i++;
	}
	if (arr_str)
		free(arr_str);
	new_arr[tmp_i++] = added_str;
	new_arr[tmp_i] = NULL;
	return (new_arr);
}

static t_par_elem	*cmd_handler(t_par_elem *substr, char ***cmd_substr)
{
	char	*str;

	str = NULL;
	while (substr && (substr->type == DEFAULT_N
							|| substr->type == OPER_DOLL_N))
	{
			utils_append_string(&str, substr->value);
			substr = substr->next;
		if (substr && substr->type != OPER_PIPE_N && substr->type != DEFAULT_N
						&& substr->type != OPER_DOLL_N)
		{
			if (substr)
				substr = substr->next;
			if (substr)
				substr = substr->next;
		}
	}
	*cmd_substr = arr_add_realloc(str, *cmd_substr);
	str = NULL;
	return (substr);
}

/*
--> return NULL - pipe on first position*/
char	**arr_cmd_formation(t_par_list *elem_list)
{
	t_par_elem	*substr;
	char	**cmd_substr;

	cmd_substr = NULL;
	substr = elem_list->begin;
	while (substr)
	{
		if (substr->type == OPER_PIPE_N)
		{
			if (elem_list->begin == substr)
				return (NULL);
			substr = substr->next;
		}
		else if (substr->type != DEFAULT_N && substr->type != OPER_DOLL_N)
		{
			if (substr)
				substr = substr->next;
			if (substr)
				substr = substr->next;
		}
		if (substr && (substr->type == DEFAULT_N
							|| substr->type == OPER_DOLL_N))
			substr = cmd_handler(substr, &cmd_substr);
	}
	return (cmd_substr);
}
