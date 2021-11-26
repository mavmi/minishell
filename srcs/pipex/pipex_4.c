/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 15:24:41 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/11/26 16:33:34 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

void	proc_destroy_elem(t_process *process)
{
	if (!process)
		return ;
	free(process->exec_name);
	free(process->exec_path);
	utils_destroy_strings_array(process->argv);
	free(process);
}

void	proc_destroy_list(t_process *list)
{
	t_process	*tmp_ptr;

	if (!list)
		return ;
	while (list)
	{
		tmp_ptr = list->next;
		proc_destroy_elem(list);
		list = tmp_ptr;
	}
}
