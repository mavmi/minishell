/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 15:54:30 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/09/11 18:33:11 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/rebuilt_funcs.h"

// Call rebuilt or original function with [argv[0]] name
void	call_func(int argc, char **argv)
{
	char	*func;
	size_t	strlen;

	func = argv[0];
	strlen = ft_strlen(func);
	if (cmp_strings(func, ECHO))
		my_echo(argc, argv);
	else if (cmp_strings(func, CD))
		my_cd(argc, argv);
	else if (cmp_strings(func, PWD))
		my_pwd();
	else if (cmp_strings(func, EXPORT))
		my_export(argc, argv);
	else if (cmp_strings(func, UNSET))
		my_unset(argc, argv);
	else if (cmp_strings(func, ENV))
		my_env();
	else if (cmp_strings(func, EXIT))
		my_exit();
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
	if (!command_strs || !ft_strlen(command)){
		destroy_strings_array(command_strs);
		return ;
	}
	argc = 0;
	tmp_ptr = command_strs;
	while (*tmp_ptr)
	{
		argc++;
		tmp_ptr++;
	}
	call_func(argc, command_strs);
	destroy_strings_array(command_strs);
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

	t_env_elem *elem = g_data->envp->begin;
	while (elem){
		printf("%s=%s\n", elem->name, elem->value);
		elem = elem->next;
	}
	printf("\n\t >>> ************* <<< \n\n\n");	


	parse_command("export PWD=2");
	elem = g_data->envp->begin;
	while (elem){
		printf("%s=%s\n", elem->name, elem->value);
		elem = elem->next;
	}

	parse_command("export a=2");
	elem = g_data->envp->begin;
	while (elem){
		printf("%s=%s\n", elem->name, elem->value);
		elem = elem->next;
	}

	env_destroy(g_data->envp);	
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
	if (input_fd < 0)
		return ;

	output_fd = proc_open_output_file("output_text");
	if (output_fd < 0)
		return ;	

	t_process	*list = proc_init_list(argv + 1, envp);
	proc_execute_list(list, input_fd, output_fd);

	close(input_fd);
	close(output_fd);
	proc_destroy_list(list);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc; (void)argv; (void)envp;
	g_data = (t_data *)malloc(sizeof(t_data));
	g_data->envp = env_create(envp);

	set_up_signals();
	while (1)
	{
		char *str = readline(PORMT);
		if (!str){
			exit(0);
		}
		parse_command(str);
		add_history(str);
		free(str);
	}
	return 0;
}
