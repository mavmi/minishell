/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 17:47:31 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/11/08 15:15:03 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

static void	redirect(t_process *proc, int input, int output)
{
	if (proc->prev)
	{
		dup2(proc->prev->output[0], STDIN_FILENO);
		close(proc->prev->output[0]);
		close(proc->prev->output[1]);
	}
	else if (input != -1 && input != STDIN_FILENO)
	{
		dup2(input, STDIN_FILENO);
		close(input);
	}
	if (proc->next)
	{
		dup2(proc->output[1], STDOUT_FILENO);
		close(proc->output[0]);
		close(proc->output[1]);
	}
	else if (output != -1 && output != STDOUT_FILENO)
	{
		dup2(output, STDOUT_FILENO);
		close(output);
	}
}

// Execute process [proc] using [input] and [output] as default
// iostreams to read and write.
// If [input] or/and [output] is -1, it will try to get iostream(s)
// from it's neighbor(s).
// If neighbor is NULL, it will use STDIN or STDOUT
void	proc_execute_default_func(t_process *proc, int input, int output)
{	
	char	**envp;

	redirect(proc, input, output);
	envp = env_get_content(g_data->envp);
	execve(proc->exec_path, proc->argv, envp);
	destroy_strings_array(envp);
}

void	proc_execute_list(t_process *list, int input, int output)
{
	int			exit_status;
	t_process	*ptr;

	if (!list)
		return ;
	ptr = list;
	while (ptr)
	{
		ptr->pid = fork();
		if (ptr->pid)
		{
			redirect(ptr, input, output);
			execve(ptr->exec_path, ptr->argv, NULL);
		}
		ptr = ptr->next;
	}
	ptr = list;
	while (ptr)
	{
		waitpid(ptr->pid, &exit_status, WNOHANG);
		close(ptr->output[1]);
		ptr = ptr->next;
	}
}
