/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 17:47:31 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/11/10 15:52:11 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

static t_process	*proc_find_first_built_in(t_process *proc)
{
	if (!proc)
		return (NULL);
	while (proc)
	{
		if (proc->is_built_in)
			return (proc);
		proc = proc->next;
	}
	return (NULL);
}

static void	proc_execute_built_ins(t_process **ptr, int in, int out)
{
	t_process	*first;

	first = *ptr;
	while (*ptr && (*ptr)->is_built_in)
	{
		(*ptr)->pid = process_execute_built_in(*ptr, in, out);
		if ((*ptr)->pid == -1)
			return ;
		(*ptr) = (*ptr)->next;
	}
	(*ptr) = first;
	while (ptr)
	{
		waitpid((*ptr)->pid, &g_data.exit_status, WNOHANG | WUNTRACED);
		if (WIFEXITED(g_data.exit_status))
			g_data.exit_status = WEXITSTATUS(g_data.exit_status);
		close((*ptr)->io_buffer[1]);
		(*ptr) = (*ptr)->next;
	}
}

void	proc_execute_list(t_process *list, int in, int out)
{
	t_process	*ptr;

	ptr = list;
	while (ptr)
	{
		if (ptr->is_built_in)
			proc_execute_built_ins(&ptr, in, out);
		while (ptr && !ptr->is_built_in)
		{
			ptr->pid = process_execute_rebuilt(ptr, in, out);
			if (ptr->pid == -1)
				return ;
			ptr = ptr->next;
		}
	}
}
