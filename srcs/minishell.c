/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 15:54:30 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/11/28 13:16:18 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/enviroment.h"
#include "../include/parser_.h"
#include "../include/processes.h"

// Signals call this function
static void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		printf("\n");
		rl_redisplay();
	}
}

// Just set up signals
static void	signals_set_up(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
}

// Increase enviroment's SHLVL value when programm starts 
static void	update_shlvl(void)
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

// Calls parser and executor untill exit
static void	run(void)
{
	char		*str;
	t_process	*proc_list;
	t_pars_list	*pars_list;

	while (1)
	{
		str = readline(PROMT);
		add_history(str);
		pars_list = pars_split(str);
		proc_list = pars_intepret(pars_list);
		proc_execute_list(proc_list);
		pars_destroy_list(pars_list);
		proc_destroy_list(proc_list);
		free(str);
	}	
	rl_clear_history();
}

int	main(int argc, char **argv, char **envp)
{
	g_data.envp = env_create(envp);
	if (!g_data.envp)
	{
		printf("Can not create local enviroment\n");
		return (1);
	}
	signals_set_up();
	update_shlvl();
	g_data.exit_status = 0;
	g_data.error = NULL;
	run();
	env_destroy(g_data.envp);
}
