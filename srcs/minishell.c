/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 15:54:30 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/12/16 18:56:06 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/enviroment.h"
#include "../include/parser.h"
#include "../include/processes.h"

// Calls parser and executor untill exit
static void	run(void)
{
	char		*str;
	t_par_list	*pars_list;

	while (1)
	{
		str = readline(PROMT);
		if (!str)
			rebuilt_exit(1, NULL);
		if (ft_strlen(str))
			add_history(str);
		pars_list = par_split(str);
		if (par_check_list(pars_list))
			par_work_steps(pars_list);
		else if (pars_list && pars_list->size)
			ft_putendl_fd("minishell: error: syntax error", STDERR_FILENO);
		par_destroy_all(pars_list);
		free(str);
	}
	rl_clear_history();
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	g_data.envp = env_create(envp);
	if (!g_data.envp)
	{
		printf("Can not create local enviroment\n");
		return (1);
	}
	par_sig_init();
	par_update_shlvl();
	g_data.exit_status = 0;
	g_data.error = NULL;
	run();
	env_destroy(g_data.envp);
}
