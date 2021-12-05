/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 17:47:31 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/12/05 16:10:48 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/processes.h"

// Part of proc_execute_list function.
// Execute only built-in's
//static void	proc_execute_built_ins(t_process **ptr)
//{
//	t_process	*first;

//	first = *ptr;
//	while (*ptr && (*ptr)->is_built_in)
//	{
//		(*ptr)->pid = process_execute_built_in(*ptr);
//		if ((*ptr)->pid == -1)
//			return ;
//		(*ptr) = (*ptr)->next;
//	}
//	(*ptr) = first;
//	while (*ptr && (*ptr)->is_built_in)
//	{
//		close((*ptr)->io_buffer[STDIN_FILENO]);
//		close((*ptr)->io_buffer[STDOUT_FILENO]);
//		waitpid((*ptr)->pid, &g_data.exit_status, 0);
//		if (WIFEXITED(g_data.exit_status))
//			g_data.exit_status = WEXITSTATUS(g_data.exit_status);
//		(*ptr) = (*ptr)->next;
//	}
//}

// Part of proc_execute_list.
// Execute only built-in's
static void	proc_execute_built_ins(t_process **ptr)
{
	t_process	*first;

	first = *ptr;
	while (*ptr && (*ptr)->is_built_in)
	{
		if ((*ptr)->input_fd == NON_FD || (*ptr)->output_fd == NON_FD)
		{
			(*ptr) = (*ptr)->next;
			continue ;
		}
		(*ptr)->pid = process_execute_built_in(*ptr);
		if ((*ptr)->pid == -1)
			return ;
		waitpid((*ptr)->pid, &g_data.exit_status, WNOHANG & WUNTRACED);
		if (WIFEXITED(g_data.exit_status))
			g_data.exit_status = WEXITSTATUS(g_data.exit_status);
		close((*ptr)->io_buffer[STDOUT_FILENO]);
		(*ptr) = (*ptr)->next;
	}
}

// Execute all commands in process list
void	proc_execute_list(t_process *list)
{
	t_process	*ptr;

	ptr = list;
	while (ptr)
	{
		if (ptr->is_built_in)
			proc_execute_built_ins(&ptr);
		while (ptr && !ptr->is_built_in)
		{
			if (ptr->input_fd != NON_FD && ptr->output_fd != NON_FD)
				process_execute_rebuilt(ptr);
			ptr = ptr->next;
		}
	}
}
