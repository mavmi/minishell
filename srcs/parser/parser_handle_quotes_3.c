/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_handle_quotes_3.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 18:55:53 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/12/21 15:40:03 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

static char	*par_get_var_value(char *name)
{
	t_env_elem	*elem;

	if (utils_cmp_strings(name, "?"))
		return (ft_itoa(g_data.exit_status));
	elem = env_get_by_name(g_data.envp, name);
	if (!elem)
		return (NULL);
	return (ft_strdup(elem->value));
}

static char	*par_get_var_name(char *str)
{
	int		i;
	char	*ptr;

	i = 0;
	if (*str == '?')
	{
		return (ft_strdup("?"));
	}
	if (*str == '$')
	{
		while (str[i] && str[i] != ' '
			&& str[i] != '\'' && str[i] != '\"')
			i++;
		return (ft_substr(str, 0, i));
	}
	ptr = par_strchr(str + i);
	if (ptr)
		return (ft_substr(str, 0, ptr - str));
	return (ft_strdup(str));
}

static void	par_parse_doll(char **str, char **output, int is_last)
{
	char	*tmp;
	char	*var_name;

	if (*(*str + 1) == 0 || *(*str + 1) == ' ')
	{
		if (is_last)
			utils_append_string(output, "$");
		*str += 1;
		return ;
	}
	var_name = par_get_var_name(*str + 1);
	*str += ft_strlen(var_name) + 1;
	tmp = par_get_var_value(var_name);
	utils_append_string(output, tmp);
	free(tmp);
	free(var_name);
}

static void	par_parse_non_doll(char **str, char **output)
{
	char	*ptr;
	char	*tmp;

	ptr = ft_strchr(*str, '$');
	if (!ptr)
	{
		tmp = ft_strdup(*str);
		utils_append_string(output, tmp);
		*str += ft_strlen(tmp);
		free(tmp);
	}
	else
	{
		tmp = ft_substr(*str, 0, ptr - *str);
		utils_append_string(output, tmp);
		*str = ptr;
		free(tmp);
	}	
}

char	*par_parse_vars(char *str, int is_last)
{
	char	*output;

	output = NULL;
	while (*str)
	{
		if (*str == '$')
		{
			par_parse_doll(&str, &output, is_last);
		}
		else
		{	
			par_parse_non_doll(&str, &output);
		}
	}
	return (output);
}
