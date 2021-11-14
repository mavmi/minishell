/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 17:11:47 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/11/14 13:51:38 by pmaryjo          ###   ########.fr       */
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

// Change working directory to [argv[1]].
// At first it tries to use [argv[1]] as absolute path
void	rebuilt_cd(int argc, char **argv)
{
	char	*old_pwd;
	char	*new_pwd;

	if (argc != 2)
		return ;
	old_pwd = getcwd(NULL, 0);
	if (chdir(argv[1]))
	{
		free(old_pwd);
		perror(strerror(errno));
		return ;
	}
	new_pwd = getcwd(NULL, 0);
	set_values(new_pwd, old_pwd);
}
