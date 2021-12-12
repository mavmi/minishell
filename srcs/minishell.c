/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 15:54:30 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/12/12 10:40:58 by pmaryjo          ###   ########.fr       */
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
		printf("\n");
		rl_redisplay();
	}
}

// Just set up signals
static void	signals_set_up(void)
{
	rl_catch_signals = 0;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

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
		{
			work_steps(pars_list);
		}
		free(str);
	}
	rl_clear_history();
}

int	main(int argc, char **argv, char **envp)
{
	//char **arg;
	//size_t size;
	//proc_split(
	//	"PWD \'asd  \'\"   qwerty\"      ",
	//	&arg,
	//	&size,
	//	0
	//);
	//char **cpy = arg;
	//while (*cpy){
	//	printf("%s|\n", *cpy);
	//	cpy++;
	//}
	//utils_destroy_strings_array(arg);
	//printf("%ld\n", size);
	//return 0;
	
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
