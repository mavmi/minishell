/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 17:11:47 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/12/15 18:55:39 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/rebuilt_funcs.h"

static void	set_values(char *new_pwd, char *old_pwd)
{
	char	*tmp;

	if (!env_set_by_name(g_data.envp, "PWD", new_pwd))
	{
		tmp = utils_create_lone_string("PWD", new_pwd);
		env_push_back(g_data.envp, tmp);
		free(new_pwd);
		free(tmp);
	}
	if (!env_set_by_name(g_data.envp, "OLDPWD", old_pwd))
	{
		tmp = utils_create_lone_string("OLDPWD", old_pwd);
		env_push_back(g_data.envp, tmp);
		free(old_pwd);
		free(tmp);
	}
}

static void	change_dir(char *new_path)
{
	char	*old_pwd;
	char	*new_pwd;

	old_pwd = getcwd(NULL, 0);
	if (chdir(new_path))
	{
		free(old_pwd);
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd(new_path, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		g_data.exit_status = 1;
		return ;
	}
	new_pwd = getcwd(NULL, 0);
	set_values(new_pwd, old_pwd);
	g_data.exit_status = 0;
}

// Change working directory to [argv[1]].
// At first it tries to use [argv[1]] as absolute path
void	rebuilt_cd(int argc, char **argv)
{
	t_env_elem	*env_elem;

	if (argc > 1)
	{
		change_dir(argv[1]);
		return ;
	}
	env_elem = env_get_by_name(g_data.envp, "HOME");
	if (!env_elem)
	{
		ft_putendl_fd("minishell: cd: HOME not set", STDERR_FILENO);
		g_data.exit_status = 1;
		return ;
	}
	change_dir(env_elem->value);
}
