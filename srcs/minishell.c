/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 15:54:30 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/09/10 15:29:44 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/rebuilt_funcs.h"

// Call rebuilt or original function with [argv[0]] name
void	call_func(int argc, char **argv)
{
	char	*func;
	size_t	strlen;

// printf("CALL ARGS\n");
// char **test = argv;
// while (*test){
// 	printf("%s\n", *test);
// 	test++;
// }

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
		env();
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

void test_gnl(void)
{
	char *line;

	int input_fd = proc_open_input_file("input_text");
	if (input_fd < 0)
		return ;
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
	g_data = (t_data *)malloc(sizeof(t_data));
	g_data->envp = env_create(envp);

	// printf("oldpwd %s\n", getcwd(0, 0));
	// chdir("include");
	// printf("pwd %s\n", getcwd(0, 0));
	// printf("\n********************************\n\n");


	// char **test = env_get_content(g_data.envp);
	// while (*test){
	// 	printf("%s\n", *test);
	// 	test++;
	// }

	// test_multipipe(argv, envp);
	// test_miltipipe_with_iofiles(argv, envp);
	// test_gnl();

	// char **ptr = env_get_content(g_data->envp);
	// char **ptr_1 = ptr;

	// printf("\n\n\t >>> ***************** <<< \n\n\n");

	// while (*ptr)
	// {
	// 	printf("%p\n", *ptr);
	// 	free(*ptr);
	// 	ptr++;	
	// }
	// printf("%p\n", ptr_1);
	// free(ptr_1);
	// return 0;


	// char *str = readline(PORMT);
	// parse_command(str);
	// free(str);
	// return 0;

	set_up_signals();
	int i = 0;
	while (i++ < 5)
	{
		char *str = readline(PORMT);
		if (!str){
			exit(0);
		}
		parse_command(str);
		add_history(str);
		free(str);
	}
	rl_clear_history();
	env_destroy(g_data->envp);
	free(g_data);
	return 0;
}
