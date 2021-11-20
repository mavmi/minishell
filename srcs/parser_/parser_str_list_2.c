/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_str_list_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 13:12:46 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/11/20 16:42:16 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser_.h"

static char	*pars_handle_double_quote(char *str)
{
	int			begin;
	int			end;
	char		*tmp;
	char		*result;
	t_env_elem	*env_elem;

	begin = 1;
	result = NULL;
	while (str[begin] != '\"')
	{
		end = begin;
		while (str[end] != '\"' && (str[end] != '$' || (str[end] == '$'
			&& (str[end + 1] == ' ' || str[end + 1] == '\"'))))
			end++;
		if (begin != end)
		{
			tmp = ft_substr(str, begin, end - begin);
			if (!tmp)
			{
				free(result);
				return (NULL);
			}
			utils_append_string(&result, tmp);
			begin += end - begin;
			free(tmp);
		}
		else
		{
			begin = ++end;
			while (str[end] != '\"' && str[end] != ' ')
				end++;
			tmp = ft_substr(str, begin, end - begin);
			if (!tmp)
			{
				free(result);
				return (NULL);
			}
			env_elem = env_get_by_name(g_data.envp, tmp);
			if (env_elem)
			{
				utils_append_string(&result, env_elem->value);
				begin += end - begin;
			}
			free(tmp);
		}
	}
	return (result);
}

// Converts t_string list into one string.
// May return NULL
char	*pars_get_whole_string(t_strings *list)
{
	char	*tmp;
	char	*string;

	if (!list)
		return (NULL);
	string = NULL;
	while (list)
	{
		if (list->string[0] == '\'')
		{
			tmp = ft_substr(list->string, 1, ft_strlen(list->string) - 2);
			if (!tmp)
			{
				free(string);
				return (NULL);
			}
			utils_append_string(&string, tmp);
			free(tmp);
		}
		else if (list->string[0] == '\"')
		{
			tmp = pars_handle_double_quote(list->string);
			if (!tmp)
			{
				free(string);
				return (NULL);
			}
			utils_append_string(&string, tmp);
			free(tmp);
		}
		else
			utils_append_string(&string, list->string);
		list = list->next;
	}
	return (string);
}
