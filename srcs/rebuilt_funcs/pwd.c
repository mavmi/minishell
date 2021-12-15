/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 16:47:13 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/12/15 19:01:10 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/rebuilt_funcs.h"

void	rebuilt_pwd(int fd_out)
{
	char		*path;
	t_env_elem	*pwd_elem;

	pwd_elem = env_get_by_name(g_data.envp, "PWD");
	if (pwd_elem)
		ft_putendl_fd(pwd_elem->value, fd_out);
	else
	{
		path = getcwd(NULL, 0);
		ft_putendl_fd(path, fd_out);
		free(path);
	}
	g_data.exit_status = 0;
}
