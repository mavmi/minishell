/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 15:33:33 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/12/04 18:44:54 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/rebuilt_funcs.h"

static int	is_valid_name(char *name)
{
	if (!name || !ft_strlen(name) || (!ft_isalpha(name[0]) && name[0] != '_'))
		return (0);
	name++;
	while (*name)
	{
		if (!ft_isalpha(*name) && !ft_isdigit(*name) && *name != '_')
			return (0);
		name++;
	}
	return (1);
}

static void	add_value(char *new_name, char *new_val)
{
	char	*str;

	if (env_set_by_name(g_data.envp, new_name, new_val))
		free(new_name);
	else
	{
		str = NULL;
		utils_append_string(&str, new_name);
		utils_append_string(&str, "=");
		utils_append_string(&str, new_val);
		env_push_back(g_data.envp, str);
		free(str);
		free(new_name);
		free(new_val);
	}
}

void	rebuilt_export(int argc, char **argv)
{
	char	*equal;
	char	*new_name;
	char	*new_val;

	if (argc != 2 || !argv[1])
		return ;
	equal = ft_strchr(argv[1], '=');
	new_name = ft_substr(argv[1], 0, equal - argv[1]);
	if (!is_valid_name(new_name))
	{
		free(new_name);
		ft_putstr_fd("export: not an identifier: ", STDERR_FILENO);
		ft_putendl_fd(new_name, STDERR_FILENO);
		return ;
	}
	new_val = ft_substr(equal + 1, 0,
			ft_strlen(argv[1]) - ft_strlen(new_name) + 1);
	add_value(new_name, new_val);
}
