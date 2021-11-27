/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_string_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 13:27:34 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/11/27 16:59:11 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser_.h"

// Part of pars_handle_substr.
// Get substr without values.
// Return 0 if everything is ok,
// 1 otherwise
static int	pars_trivial_substr(char *str, char **result, int *begin, int *end)
{
	char	*tmp;

	tmp = ft_substr(str, *begin, *end - *begin);
	if (!tmp)
	{
		free(*result);
		return (1);
	}
	utils_append_string(result, tmp);
	*begin += *end - *begin;
	free(tmp);
	return (0);
}

// Part of pars_handle_substr.
// Handle values.
// Return 0 if everything is ok
// 1 otherwise
static int	pars_value_substr(char *str, char **result, int *begin, int *end)
{
	char		*tmp;
	t_env_elem	*env_elem;

	*begin = ++(*end);
	while (str[*end] && str[*end] != ' ')
		(*end)++;
	tmp = ft_substr(str, *begin, *end - *begin);
	if (!tmp)
	{
		free(result);
		return (1);
	}
	env_elem = env_get_by_name(g_data.envp, tmp);
	if (env_elem)
		utils_append_string(result, env_elem->value);
	else if (!env_elem && utils_cmp_strings(tmp, QUES_S))
		utils_append_string(result, ft_itoa(g_data.exit_status));
	else
		utils_append_string(result, "");
	*begin += *end - *begin;
	free(tmp);
	return (0);
}

// Get substring and replace names of values with values.
// May return NULL
char	*pars_handle_substr(char *str)
{
	int			begin;
	int			end;
	char		*result;

	begin = 0;
	result = NULL;
	while (str[begin])
	{
		end = begin;
		while (str[end] && (str[end] != '$' || (str[end] == '$'
					&& (str[end + 1] == ' ' || !str[end + 1]))))
			end++;
		if ((begin != end && pars_trivial_substr(str, &result, &begin, &end))
			|| (begin == end && pars_value_substr(str, &result, &begin, &end)))
			return (NULL);
	}
	return (result);
}
