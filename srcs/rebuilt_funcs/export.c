/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 15:33:33 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/12/11 17:10:39 by pmaryjo          ###   ########.fr       */
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

static void	handle_input(char *arg)
{
	char	*equal;
	char	*new_name;
	char	*new_val;

	equal = ft_strchr(arg, '=');
	if (equal)
		new_name = ft_substr(arg, 0, equal - arg);
	else
		new_name = ft_strdup(arg);
	if (!is_valid_name(new_name))
	{
		free(new_name);
		ft_putstr_fd("export: not an identifier: ", STDERR_FILENO);
		ft_putendl_fd(new_name, STDERR_FILENO);
		return ;
	}
	if (equal)
		new_val = ft_substr(equal + 1, 0,
				ft_strlen(arg) - ft_strlen(new_name) + 1);
	else
		new_val = ft_strdup("");
	add_value(new_name, new_val);
}

static void	export_output_oy_boy(int fd_out)
{
	t_enviroment	*list;
	char			**arr_list;
	int				tmp;
	size_t			size;

	tmp = 0;
	list = env_sort();
	arr_list = env_get_content(list, 1);
	while (arr_list && arr_list[tmp])
	{
		size = ft_strlen(arr_list[tmp]);
		if (size && arr_list[tmp++][--size] == '=')
			arr_list[tmp - 1][size] = '\0';
	}
	while (arr_list && *arr_list)
	{
		ft_putstr_fd("declare -x ", fd_out);
		ft_putendl_fd(*arr_list, fd_out);
		arr_list++;
	}
}

void	rebuilt_export(int argc, char **argv, int fd_out)
{
	int	i;

	if (!argv)
		return ;
	if (argc == 1)
	{
		export_output_oy_boy(fd_out);
		return ;
	}
	i = 1;
	while (i < argc)
		handle_input(argv[i++]);
}
