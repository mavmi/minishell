/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalena <msalena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 15:54:30 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/12/05 14:06:15 by msalena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/enviroment.h"
#include "../include/parser.h"
#include "../include/processes.h"

// Signals call this function
static void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		printf("  \n");
	}
}

// Just set up signals
static void	signals_set_up(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
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

static void	work_steps(t_par_list *pars_list)
{
	char		**arr_cmd;
	int			*arr_fd;
	char		**arr_env;
	t_process	*proc_list;

	arr_cmd = arr_cmd_formation(pars_list);
	arr_cmd = par_handle_quotesNenv(arr_cmd);
	arr_fd = arr_fd_formation(pars_list);
	arr_env = env_get_content(g_data.envp);
	proc_list = proc_init_list(arr_cmd, arr_fd, arr_env);
	proc_execute_list(proc_list);
	utils_destroy_strings_array(arr_cmd);
	free(arr_fd);
	proc_destroy_list(proc_list);
	par_destroy_all(pars_list);
	utils_destroy_strings_array(arr_env);
}

// Calls parser and executor untill exit
static void	run(void)
{
	char		*str;
	t_par_list	*pars_list;

	while (1)
	{
		str = readline(PROMT);
		add_history(str);
		pars_list = par_split(str);
		if (par_check_list(pars_list))
		{
			work_steps(pars_list);
		}
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
	signals_set_up();
	update_shlvl();
	g_data.exit_status = 0;
	g_data.error = NULL;
	run();
	env_destroy(g_data.envp);
}
