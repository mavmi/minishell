/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_str_list_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 13:12:46 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/11/20 19:59:14 by pmaryjo          ###   ########.fr       */
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

	begin = 0;
	result = NULL;
	while (str[begin])
	{
		end = begin;
		while (str[end] && (str[end] != '$' || (str[end] == '$'
			&& (str[end + 1] == ' ' || !str[end + 1]))))
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
			while (str[end] && str[end] != ' ')
				end++;
			tmp = ft_substr(str, begin, end - begin);
			if (!tmp)
			{
				free(result);
				return (NULL);
			}
			env_elem = env_get_by_name(g_data.envp, tmp);
			if (env_elem)
				utils_append_string(&result, env_elem->value);
			else
				utils_append_string(&result, "");
			begin += end - begin;
			free(tmp);
		}
	}
	return (result);
}

char	*pars_get_whole_string(char *input)
{
	char	*tmp;
	char	*quote_1;
	char	*quote_2;
	char	*substr;
	char	*string;

	if (!input)
		return (NULL);
	string = NULL;
	while (*input)
	{
		if (*input == '\'')
		{
			quote_1 = ft_strchr(input + 1, '\'');
			if (!quote_1)
			{
				free(string);
				return (NULL);
			}
			substr = ft_substr(input, 1, quote_1 - input - 1);
			if (!substr)
			{
				free(string);
				return (NULL);
			}
			input += ft_strlen(substr) + 2;
			utils_append_string(&string, substr);
			free(substr);
			continue ;
		}
		else if (*input == '\"')
		{
			quote_1 = ft_strchr(input + 1, '\"');
			if (!quote_1)
			{
				free(string);
				return (NULL);
			}
			substr = ft_substr(input, 1, quote_1 - input - 1);
			if (!substr)
			{
				free(string);
				return (NULL);
			}
			input += ft_strlen(substr) + 2;
			tmp = pars_handle_double_quote(substr);
			if (!tmp)
			{
				free(string);
				return (NULL);
			}
			utils_append_string(&string, tmp);
			free(tmp);
			free(substr);
		}
		else
		{
			quote_1 = ft_strchr(input, '\'');
			quote_2 = ft_strchr(input, '\"');
			if (quote_1 && quote_2 && quote_2 - quote_1 < 0)
				quote_1 = quote_2;
			if (quote_1)
				substr = ft_substr(input, 0, quote_1 - input);
			else
				substr = ft_strdup(input);
			if (!substr)
			{
				free(string);
				return (NULL);
			}
			input += ft_strlen(substr);
			tmp = pars_handle_double_quote(substr);
			if (!tmp)
			{
				free(string);
				return (NULL);
			}
			utils_append_string(&string, tmp);
			free(tmp);
			free(substr);
		}
	}
	return (string);
}
