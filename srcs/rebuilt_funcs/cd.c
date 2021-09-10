/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 17:11:47 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/09/10 15:29:16 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/rebuilt_funcs.h"

// Change working directory to [argv[1]].
// At first it tries to use [argv[1]] as absolute path
void	cd(int argc, char **argv)
{
	char	*tmp;
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
	env_set_by_name(g_data->envp, "PWD", new_pwd);
	env_set_by_name(g_data->envp, "OLDPWD", old_pwd);
}
