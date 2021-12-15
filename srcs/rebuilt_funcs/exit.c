/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 13:11:22 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/12/15 18:57:41 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/rebuilt_funcs.h"

void	rebuilt_exit(int argc, char **argv)
{
	unsigned char	status;

	if (argc == 1)
		status = 0;
	else if (argc == 2)
	{
		status = ft_atoi(*(argv + 1));
		if (ft_atoi(argv[1]) == 0 && !utils_cmp_strings(argv[1], "0"))
		{
			status = 255;
			ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
			ft_putstr_fd(argv[1], STDERR_FILENO);
			ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		}
	}
	else
	{
		ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
		g_data.exit_status = 1;
		return ;
	}
	rl_clear_history();
	env_destroy(g_data.envp);
	g_data.exit_status = 0;
	exit((int)status);
}
