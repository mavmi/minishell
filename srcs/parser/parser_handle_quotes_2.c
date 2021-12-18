/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_handle_quotes_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 16:25:34 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/12/18 16:04:31 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

static char	*par_get_non_quote_substr(char **cmd)
{	
	char	*ptr_1;
	char	*ptr_2;
	char	*substr;

	ptr_1 = ft_strchr(*cmd, '\'');
	ptr_2 = ft_strchr(*cmd, '\"');
	if (!ptr_1 && !ptr_2)
		substr = ft_strdup(*cmd);
	else if (ptr_1 && !ptr_2)
		substr = ft_substr(*cmd, 0, ptr_1 - *cmd);
	else if (!ptr_1 && ptr_2)
		substr = ft_substr(*cmd, 0, ptr_2 - *cmd);
	else
	{
		if (ptr_2 < ptr_1)
			ptr_1 = ptr_2;
		substr = ft_substr(*cmd, 0, ptr_1 - *cmd);
	}
	*cmd += ft_strlen(substr);
	return (substr);
}

static char	*par_get_quotes_substr(char **cmd, char q)
{
	char	*quote;
	char	*substr;

	quote = ft_strchr(*cmd + 1, q);
	substr = ft_substr(*cmd, 1, quote - *cmd - 1);
	*cmd += ft_strlen(substr) + 2;
	return (substr);
}

static void	par_handle_vars(char *cmd, int quote, char **output, char *substr)
{
	char	*tmp;

	if (quote)
		tmp = par_parse_vars(substr, 1);
	else
		tmp = par_parse_vars(substr, *cmd == 0);
	utils_append_string(output, tmp);
	free(tmp);
}

static void	par_handle_substr(char **cmd, char **output, int hand_vars)
{
	int		quote;
	char	*substr;

	if (**cmd == '\'')
	{
		substr = par_get_quotes_substr(cmd, '\'');
		utils_append_string(output, substr);
		free(substr);
		return ;
	}
	quote = 1;
	if (**cmd == '\"')
		substr = par_get_quotes_substr(cmd, '\"');
	else
	{
		quote = 0;
		substr = par_get_non_quote_substr(cmd);
	}
	if (hand_vars)
		par_handle_vars(*cmd, quote, output, substr);
	else
		utils_append_string(output, substr);
	free(substr);
}

char	*par_parse_quotes_and_vars(char *cmd, int hand_vars)
{
	char	*output;

	output = ft_strdup("");
	while (*cmd)
	{
		par_handle_substr(&cmd, &output, hand_vars);
	}
	return (output);
}
