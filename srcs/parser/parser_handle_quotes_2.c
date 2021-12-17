/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_handle_quotes_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 16:25:34 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/12/17 19:28:09 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

static char	*non_quote(char **cmd)
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

static char	*quotes(char **cmd, char q)
{
	char	*quote;
	char	*substr;

	quote = ft_strchr(*cmd + 1, q);
	substr = ft_substr(*cmd, 1, quote - *cmd - 1);
	*cmd += ft_strlen(substr) + 2;
	return (substr);
}

static void	vvvars(char *cmd, int quote, char **output, char *substr)
{
	char	*tmp;

	if (quote)
		tmp = vars(substr, 1);
	else
		tmp = vars(substr, *cmd == 0);
	utils_append_string(output, tmp);
	free(tmp);
}

static void	substr_(char **cmd, char **output, int hand_vars)
{
	int		quote;
	char	*substr;

	if (**cmd == '\'')
	{
		substr = quotes(cmd, '\'');
		utils_append_string(output, substr);
		free(substr);
		return ;
	}
	quote = 1;
	if (**cmd == '\"')
		substr = quotes(cmd, '\"');
	else
	{
		quote = 0;
		substr = non_quote(cmd);
	}
	if (hand_vars)
		vvvars(*cmd, quote, output, substr);
	else
		utils_append_string(output, substr);
	free(substr);
}

char	*par_handle_str(char *cmd, int hand_vars)
{
	char	*output;

	output = ft_strdup("");
	while (*cmd)
	{
		substr_(&cmd, &output, hand_vars);
	}
	return (output);
}
