/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 17:47:31 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/11/09 17:08:31 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

// STDIN_FILENO = 0
// STDOUT_FILENO = 1
// pipe[0] -> read
// pipe[1] -> write
static void	redirect(t_process *proc, int input, int output)
{
	if (proc->prev)
	{
		dup2(proc->prev->io_buffer[0], STDIN_FILENO);
		close(proc->prev->io_buffer[0]);
		close(proc->prev->io_buffer[1]);
	}
	else if (input != -1 && input != STDIN_FILENO)
	{
		dup2(input, STDIN_FILENO);
		close(input);
	}
	if (proc->next)
	{
		dup2(proc->io_buffer[1], STDOUT_FILENO);
		close(proc->io_buffer[0]);
		close(proc->io_buffer[1]);
	}
	else if (output != -1 && output != STDOUT_FILENO)
	{
		dup2(output, STDOUT_FILENO);
		close(output);
	}
}

static pid_t	process_execute(t_process *process, int input, int output)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		perror(strerror(errno));
	if (pid == 0)
	{
		redirect(process, input, output);
		if (execve(process->exec_path, process->argv, NULL) == -1)
		{
			if (process->exec_path)
				perror(strerror(errno));
			else
			{
				ft_putstr_fd(process->exec_name, STDERR_FILENO);
				ft_putendl_fd(": programm not found", STDERR_FILENO);
			}
			exit(BAD_STATUS);
		}
	}
	return (pid);
}

void	proc_execute_list(t_process *list, int input, int output)
{
	int			exit_status;
	t_process	*ptr;

	while (ptr)
	{
		ptr->pid = process_execute(ptr, input, output);
		if (ptr->pid == -1)
			return ;
		ptr = ptr->next;
	}
	ptr = list;
	while (ptr)
	{
		waitpid(ptr->pid, &exit_status, 0);
		if (WIFEXITED(exit_status))
			exit_status = WEXITSTATUS(exit_status);
		close(ptr->io_buffer[1]);
		ptr = ptr->next;
	}
}
