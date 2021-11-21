/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_string_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 13:12:46 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/11/21 14:32:56 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser_.h"

static int	pars_quotes_handler(char **input, char **string,
	char **substr, int quote_num)
{
	char	*quote_ptr;

	if (quote_num == 1)
		quote_ptr = ft_strchr(*input + 1, '\'');
	else
		quote_ptr = ft_strchr(*input + 1, '\"');
	if (!quote_ptr)
	{
		free(*string);
		return (1);
	}
	*substr = ft_substr(*input, 1, quote_ptr - *input - 1);
	if (!*substr)
	{
		free(*string);
		return (1);
	}
	return (0);
}

static int	pars_quotes(char **input, char **string, int quote_num)
{
	char	*tmp;
	char	*substr;

	if (pars_quotes_handler(input, string, &substr, quote_num))
		return (1);
	*input += ft_strlen(substr) + 2;
	if (quote_num == 1)
		utils_append_string(string, substr);
	else
	{
		tmp = pars_handle_substr(substr);
		if (!tmp)
		{
			free(*string);
			return (1);
		}										
		utils_append_string(string, tmp);
		free(tmp);
	}
	free(substr);
	return (0);
}

static char	*pars_substr_handler(char **input)
{
	char	*quote_1;
	char	*quote_2;

	quote_1 = ft_strchr(*input, '\'');
	quote_2 = ft_strchr(*input, '\"');
	if (quote_1 && quote_2 && quote_2 - quote_1 < 0)
		quote_1 = quote_2;
	if (quote_1)
		return (ft_substr(*input, 0, quote_1 - *input));
	else
		return (ft_strdup(*input));
}

static int	pars_substr(char **input, char **string)
{
	char	*substr;
	char	*tmp;

	substr = pars_substr_handler(input);
	if (!substr)
	{
		free(*string);
		return (1);
	}
	*input += ft_strlen(substr);
	tmp = pars_handle_substr(substr);
	if (!tmp)
	{
		free(*string);
		return (1);
	}
	utils_append_string(string, tmp);
	free(tmp);
	free(substr);
	return (0);
}

char	*pars_get_whole_string(char *input)
{
	int		quote_num;
	char	*string;

	if (!input)
		return (NULL);
	string = NULL;
	while (*input)
	{
		quote_num = 0;
		if (*input == '\'')
			quote_num = 1;
		else if (*input == '\"')
			quote_num = 2;
		if ((quote_num && pars_quotes(&input, &string, quote_num))
			|| (!quote_num && pars_substr(&input, &string)))
			return (NULL);
	}
	return (string);
}
