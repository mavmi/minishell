/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 15:54:30 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/11/25 15:36:09 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/rebuilt_funcs.h"

void test_print_list(t_process* list){
	if (!list){
		printf("List ptr is NULL\n");
		return;
	}

	while (list){
		printf("is built-in: %d\n", list->is_built_in);
		printf("input file: %s\n", list->input_file);
		printf("output file: %s\n", list->output_file);
		printf("exec name: %s\n", list->exec_name);
		printf("exec path: %s\n", list->exec_path);
		
		char **ptr = list->argv;
		printf("argv: ");
		while (*ptr){
			printf("%s  ", *ptr);
			ptr++;
		}
		printf("\n\n");

		list = list->next;
	}
}

void	test_double_redirect(char** envp, char *input_file, char *output_file){
	(void) input_file; (void) output_file;

	char** dirs = proc_get_paths_array(envp);

	t_process* list = proc_get_new_elem("env", dirs, NULL, input_file);
	proc_push_back(&list, proc_get_new_elem("git", dirs, NULL, output_file));

	proc_execute_list(list);

	proc_destroy_list(list);
	utils_destroy_strings_array(dirs);
}

// ********************************** //
// ********************************** //

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

	// **************************** //

	test_double_redirect(envp, "input", "output");
	env_destroy(g_data.envp);	
}
