/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 15:54:30 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/11/26 18:46:02 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/rebuilt_funcs.h"

void print_pars_list(t_pars_list* list){
	if (!list){
		printf("Pars list ptr is NULL\n");
		return;
	}

	while (list){
		printf("type: %d\n", list->type);
		printf("value: %s\n", list->value);
		list = list->next;
	}
}

void print_proc_list(t_process* list){
	if (!list){
		printf("Proc list ptr is NULL\n");
		return;
	}

	while (list){
		printf(" >> addr: %p\n", list);
		printf("is built-in: %d\n", list->is_built_in);
		printf("input fd: %d\n", list->input_fd);
		printf("output fd: %d\n", list->output_fd);
		printf("exec name: %s\n", list->exec_name);
		printf("exec path: %s\n", list->exec_path);
		printf("prev: %p\n", list->prev);
		printf("next: %p\n", list->next);
		
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

void test_paths(){
	char* path = proc_parse_cmd("../minishell/minishell");
	printf("\t >> %s\n", path);
	free(path);
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
	signals_set_up();
	update_shlvl();
	g_data.vars = NULL;
	g_data.exit_status = 0;

	// **************************** //

	char **dirs = proc_get_paths_array(envp);


	while (1)
	{
		char *str = readline(PROMT);
		add_history(str);
		
		t_pars_list* pars_list = pars_split(str);
		t_process* proc_list = pars_intepret(pars_list);
		
		//printf("\t** PARS_LIST **\n");
		//print_pars_list(pars_list);
		
		//printf("\n\t** PROC_LIST **\n");
		//print_proc_list(proc_list);
		//printf("\t*********\n\n");

		proc_execute_list(proc_list);
		
		pars_destroy_list(pars_list);
		proc_destroy_list(proc_list);

		free(str);
	}	
	rl_clear_history();


	utils_destroy_strings_array(dirs);
	env_destroy(g_data.envp);	
}
