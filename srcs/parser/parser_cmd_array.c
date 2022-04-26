/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd_array.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 17:51:02 by msalena           #+#    #+#             */
/*   Updated: 2021/12/16 14:42:11 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

int	fd_arr_len(int *fd_arr)
{
	int	size;

	if (!fd_arr)
		return (0);
	size = 0;
	while (fd_arr[size] != END_OF_FD_ARR)
		size++;
	return (size);
}

static char	**arr_cmd_add_realloc(char *added_str, char **arr_str)
{
	char	**new_arr;
	int		tmp_i;

	tmp_i = 0;
	while (arr_str && arr_str[tmp_i])
		tmp_i++;
	new_arr = (char **)malloc(sizeof(char *) * (tmp_i + 2));
	if (!new_arr)
	{
		free(added_str);
		utils_destroy_strings_array(arr_str);
		return (NULL);
	}
	tmp_i = 0;
	while (arr_str && arr_str[tmp_i])
	{
		new_arr[tmp_i] = arr_str[tmp_i];
		tmp_i++;
	}
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
	*cmd_substr = arr_cmd_add_realloc(str, *cmd_substr);
	if (!(*cmd_substr))
		return (NULL);
	str = NULL;
	return (substr);
}

/* Formations new arr which consists of cmd strs*/
char	**arr_cmd_formation(t_par_list *elem_list)
{
	t_par_elem	*substr;
	char		**cmd_substr;

	if (!elem_list && !elem_list->begin)
		return (NULL);
	cmd_substr = NULL;
	substr = elem_list->begin;
	while (substr)
	{
		if (substr && substr->type == OPER_PIPE_N)
			substr = substr->next;
		else if (substr && substr->type != OPER_PIPE_N
			&& substr->type != OPER_DOLL_N && substr->type != DEFAULT_N)
		{
			substr = substr->next;
			substr = substr->next;
		}
		else if (substr && (substr->type == DEFAULT_N
				|| substr->type == OPER_DOLL_N))
			substr = cmd_handler(substr, &cmd_substr);
		if (!substr && !cmd_substr)
			return (NULL);
	}
	return (cmd_substr);
}
