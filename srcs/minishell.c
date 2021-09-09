/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 15:54:30 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/09/09 21:10:12 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/rebuilt_funcs.h"

// Call rebuilt or original function with [argv[0]] name
void	call_func(int argc, char **argv)
{
	char	*func;
	size_t	strlen;

	(void)argc;
	func = argv[0];
	strlen = ft_strlen(func);
	if (cmp_strings(func, ECHO))
		(void)strlen;
	else if (cmp_strings(func, CD))
		cd(argc, argv);
	else if (cmp_strings(func, PWD))
		pwd();
	else if (cmp_strings(func, EXPORT))
		(void)strlen;
	else if (cmp_strings(func, UNSET))
		(void)strlen;
	else if (cmp_strings(func, ENV))
		(void)strlen;
	else if (cmp_strings(func, EXIT))
		(void)strlen;
	else
		(void)strlen;
}

// Get command string [char *command] from terminal
// and split by spaces into [char **argv]
void	parse_command(char *command)
{
	int		argc;
	char	**tmp_ptr;
	char	**command_strs;

	command_strs = ft_split(command, ' ');
	if (!command_strs || !ft_strlen(command))
		return ;
	argc = 0;
	tmp_ptr = command_strs;
	while (*tmp_ptr)
	{
		argc++;
		tmp_ptr++;
	}
	call_func(argc, command_strs);
	free(command_strs);
}

void print_strings_array(char **strings)
{
	while (*strings){
		printf(" > %s\n", *strings);
		strings++;
	}	
}

void test_env(int argc, char **argv, char **envp)
{
	(void)argc; (void)argv; (void)envp;

	t_enviroment *env = env_create(envp);
	if (!env){
		printf("ENV = NULL\n");
	} else {
		t_env_elem *elem = env->begin;
		while (elem){
			printf("%s=%s\n", elem->name, elem->value);
			elem = elem->next;
		}
	}	
	env_destroy(env);	
}

void test_multipipe(char **argv, char **envp)
{
	t_process	*list = proc_init_list(argv + 1, envp);
	proc_execute_list(list, -1, -1);
	proc_destroy_list(list);
}

void test_miltipipe_with_iofiles(char **argv, char **envp)
{
	int input_fd;
	int output_fd;

	input_fd = proc_open_input_file("input_text");
	output_fd = proc_open_output_file("output_text");

	t_process	*list = proc_init_list(argv + 1, envp);
	proc_execute_list(list, input_fd, output_fd);

	close(input_fd);
	close(output_fd);
	proc_destroy_list(list);
}

void test_gnl(void)
{
	char *line;

	int input_fd = proc_open_input_file("input_text");
	while(1){
		if (get_next_line(input_fd, &line) <= 0 || !line)
			break;
		printf("%s\n", line);	
	}
	close(input_fd);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc; (void)argv; (void)envp;
	g_data.envp = env_create(envp);


	// test_multipipe(argv, envp);
	// test_miltipipe_with_iofiles(argv, envp);
	test_gnl();

	set_up_signals();
	while (1)
	{
		char *str = readline(PORMT);
		if (!str){
			exit(0);
		}
		add_history(str);
		free(str);
	}
	rl_clear_history();
	env_destroy(g_data.envp);
	return 0;
}
