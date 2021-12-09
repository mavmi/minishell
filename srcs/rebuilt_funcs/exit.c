/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 13:11:22 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/12/09 20:42:51 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/rebuilt_funcs.h"

void	rebuilt_exit(int argc, char **argv)
{
	int	status;

	if (argc == 1)
		status = 0;
	else if (argc == 2)
		status = ft_atoi(*(argv + 1));
	else
	{
		ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
		return ;
	}
	rl_clear_history();
	env_destroy(g_data.envp);
	exit(status);
}
