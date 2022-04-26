/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 15:33:33 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/12/18 19:05:35 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/rebuilt_funcs.h"

static void	handle_input(char *arg)
{
	char	*equal;
	char	*new_name;

	equal = ft_strchr(arg, '=');
	if (equal)
		new_name = ft_substr(arg, 0, equal - arg);
	else
		new_name = ft_strdup(arg);
	if (!rebuilt_is_valid_name(new_name))
	{
		ft_putstr_fd("export: not an identifier: ", STDERR_FILENO);
		ft_putendl_fd(arg, STDERR_FILENO);
		free(new_name);
		g_data.exit_status = 1;
		return ;
	}
	if (equal)
		add_value(new_name, ft_substr(equal + 1, 0,
				ft_strlen(arg) - ft_strlen(new_name) + 1));
	else
		add_value(new_name, NULL);
}

static void	print_value(char *str, int fd_out)
{
	char	*eq;
	char	*name;
	char	*value;

	eq = ft_strchr(str, '=');
	if (!eq)
		return ;
	name = ft_substr(str, 0, eq - str);
	value = ft_substr(eq + 1, 0, ft_strlen(eq + 1));
	if (name && value)
	{
		ft_putstr_fd("declare -x ", fd_out);
		ft_putstr_fd(name, fd_out);
		ft_putstr_fd("=\"", fd_out);
		ft_putstr_fd(value, fd_out);
		ft_putendl_fd("\"", fd_out);
	}
	free(name);
	free(value);
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
	size = 0;
	while (arr_list && arr_list[size])
	{
		print_value(arr_list[size], fd_out);
		size++;
	}
	env_destroy(list);
	utils_destroy_strings_array(arr_list);
}

void	rebuilt_export(int argc, char **argv, int fd_out)
{
	int	i;

	if (!argv)
		return ;
	g_data.exit_status = 0;
	if (argc == 1)
	{
		export_output_oy_boy(fd_out);
		return ;
	}
	i = 1;
	while (i < argc)
		handle_input(argv[i++]);
}
