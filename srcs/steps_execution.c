/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   steps_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalena <msalena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 18:18:17 by msalena           #+#    #+#             */
/*   Updated: 2021/12/05 18:21:25 by msalena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

// Increase enviroment's SHLVL value when programm starts
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

void	work_steps(t_par_list *pars_list)
{
	char		**arr_cmd;
	int			*arr_fd;
	char		**arr_env;
	t_process	*proc_list;

	arr_cmd = arr_cmd_formation(pars_list);
	arr_cmd = par_handle_quotesNenv(arr_cmd);
	arr_fd = arr_fd_formation(pars_list->begin);
	arr_env = env_get_content(g_data.envp);
	proc_list = proc_init_list(arr_cmd, arr_fd, arr_env);
	proc_execute_list(proc_list);
	utils_destroy_strings_array(arr_cmd);
	free(arr_fd);
	proc_destroy_list(proc_list);
	par_destroy_all(pars_list);
	utils_destroy_strings_array(arr_env);
}
