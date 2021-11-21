/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 15:54:30 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/11/21 17:00:30 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/rebuilt_funcs.h"

void	update_shlvl(void)
{
	int			shlvl;
	t_env_elem	*env_elem;

	env_elem = env_get_by_name(g_data.envp, "SHLVL");
	if (!env_elem)
		env_push_back(g_data.envp, "SHLVL=1");
	else
	{
		shlvl = ft_atoi(env_elem->value);
		free(env_elem->value);
		env_elem->value = ft_itoa(shlvl + 1);
	}
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;	(void)argv;	(void)envp;

	g_data.envp = env_create(envp);
	if (!g_data.envp)
	{
		printf("Can not create local enviroment\n");
		return (1);
	}
	update_shlvl();
	g_data.vars = NULL;
	g_data.exit_status = 0;
}
