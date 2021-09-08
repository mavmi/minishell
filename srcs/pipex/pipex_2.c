/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 17:47:31 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/09/08 20:25:46 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

static void	execute_default_func(t_process *proc)
{
	char	**envp;

	if (proc->prev)
	{
		dup2(proc->prev->output[0], STDIN_FILENO);
		close(proc->prev->output[0]);
		close(proc->prev->output[1]);
	}
	if (proc->next)
	{
		dup2(proc->output[1], STDOUT_FILENO);
		close(proc->output[0]);
		close(proc->output[1]);
	}
	envp = env_get_content(g_data.envp);
	execve(proc->exec_path, proc->argv, envp);
	destroy_strings_array(envp);
}

void	proc_execute_list(t_process *list)
{
	int			exit_status;
	pid_t		pid;
	t_process	*ptr;

	if (!list)
		return ;
	ptr = list;
	while (ptr)
	{
		pid = fork();
		if (!pid)
			execute_default_func(ptr);
		waitpid(pid, &exit_status, WNOHANG);
		close(ptr->output[1]);
		ptr = ptr->next;
	}
}
