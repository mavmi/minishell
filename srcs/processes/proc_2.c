/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 15:24:41 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/11/27 17:05:45 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/processes.h"

// Destroy process element
void	proc_destroy_elem(t_process *process)
{
	if (!process)
		return ;
	free(process->exec_name);
	free(process->exec_path);
	utils_destroy_strings_array(process->argv);
	free(process);
}

// Destroy whole process list
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
