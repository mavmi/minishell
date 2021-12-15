/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_handle_quotes_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 16:25:34 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/12/15 18:01:23 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

static char	*par_call_vars_handler(char *str, int hand_vars)
{
	if (hand_vars)
		return (par_handle_vars(str));
	return (ft_strdup(str));
}

static char	*par_handle_quote_substr(char **cmd, int hand_vars)
{
	char	*quote;
	char	*substr;
	char	*parsed_substr;

	quote = ft_strchr(*cmd + 1, **cmd);
	if (!quote)
		return (NULL);
	else
		substr = ft_substr(*cmd, 1, quote - *cmd - 1);
	if (**cmd == '\"')
		parsed_substr = par_call_vars_handler(substr, hand_vars);
	else
		parsed_substr = ft_strdup(substr);
	*cmd += ft_strlen(substr) + 2;
	free(substr);
	return (parsed_substr);
}

static char	*par_handle_non_quote_substr(char **cmd, int hand_vars)
{
	char	*quote_1;
	char	*quote_2;
	char	*substr;
	char	*parsed_substr;

	quote_1 = ft_strchr(*cmd, '\'');
	quote_2 = ft_strchr(*cmd, '\"');
	if (!quote_1 && !quote_2)
		substr = ft_strdup(*cmd);
	else if (quote_1 && !quote_2)
		substr = ft_substr(*cmd, 0, quote_1 - *cmd);
	else if (!quote_1 && quote_2)
		substr = ft_substr(*cmd, 0, quote_2 - *cmd);
	else
	{
		if (quote_2 < quote_1)
			quote_1 = quote_2;
		substr = ft_substr(*cmd, 0, quote_1 - *cmd);
	}
	parsed_substr = par_call_vars_handler(substr, hand_vars);
	*cmd += ft_strlen(substr);
	free(substr);
	return (parsed_substr);
}

char	*par_handle_str(char *cmd, int hand_vars)
{
	char	*output;
	char	*parsed_substr;	

	if (!cmd)
		return (NULL);
	output = ft_strdup("");
	while (*cmd)
	{
		if (*cmd != '\'' && *cmd != '\"')
			parsed_substr = par_handle_non_quote_substr(&cmd, hand_vars);
		else
			parsed_substr = par_handle_quote_substr(&cmd, hand_vars);
		utils_append_string(&output, parsed_substr);
		free(parsed_substr);
	}
	return (output);
}
