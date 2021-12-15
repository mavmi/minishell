/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_handle_quotes_3.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 16:36:10 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/12/15 18:19:07 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

static void	par_handle_non_percent(char **substr, char **output)
{
	char	*tmp;
	char	*ptr;

	ptr = ft_strchr(*substr, '$');
	if (!ptr)
	{
		utils_append_string(output, *substr);
		*substr += ft_strlen(*substr);
		return ;
	}
	tmp = ft_substr(*substr, 0, ptr - *substr);
	utils_append_string(output, tmp);
	*substr += ft_strlen(tmp);
	free(tmp);
}

static void	par_handle_percent(char **substr, char **output)
{
	char		*ptr;
	char		*var_name;
	t_env_elem	*env_elem;

	(*substr)++;
	ptr = ft_strchr(*substr, ' ');
	if (!ptr)
		ptr = ft_strchr(*substr, '\'');
	if (!ptr)
		ptr = ft_strchr(*substr, '\"');
	if (!ptr)
		ptr = ft_strchr(*substr, '$');
	if (ptr)
		var_name = ft_substr(*substr, 0, ptr - *substr);
	else
		var_name = ft_strdup(*substr);
	env_elem = env_get_by_name(g_data.envp, var_name);
	if (env_elem)
		utils_append_string(output, env_elem->value);
	else
		utils_append_string(output, "");
	*substr += ft_strlen(var_name);
	free(var_name);
}

static void	par_uppender(char **output)
{
	char	*tmp;

	tmp = ft_itoa(g_data.exit_status);
	utils_append_string(output, tmp);
	free (tmp);
}

char	*par_handle_vars(char *substr)
{
	char	*output;

	if (!substr)
		return (NULL);
	output = NULL;
	while (*substr)
	{
		if (*substr != '$')
			par_handle_non_percent(&substr, &output);
		else if (*(substr + 1) == ' ' || *(substr + 1) == 0)
		{
			utils_append_string(&output, "$");
			substr++;
		}
		else if (*(substr + 1) == '?')
		{
			par_uppender(&output);
			substr += 2;
		}
		else
			par_handle_percent(&substr, &output);
	}
	return (output);
}