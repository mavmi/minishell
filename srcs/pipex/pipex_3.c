/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 17:36:19 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/11/12 14:11:02 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

// STDIN_FILENO = 0
// STDOUT_FILENO = 1
// pipe[0] -> read
// pipe[1] -> write
static void	proc_redirect(t_process *proc, int input, int output)
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

pid_t	process_execute_built_in(t_process *process, int in, int out)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		perror(strerror(errno));
	if (pid == 0)
	{
		proc_redirect(process, in, out);
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

pid_t	process_execute_rebuilt(t_process *process, int out)
{
	int		argc;
	pid_t	pid;
	char	**ptr;

	argc = 0;
	ptr = process->argv;
	while (*ptr)
	{
		ptr++;
		argc++;
	}
	if (process->next)
	{
		rebuilt_call_func(argc, process->argv,
			process->io_buffer[STDOUT_FILENO]);
		close(process->io_buffer[STDOUT_FILENO]);
	}
	else
	{
		rebuilt_call_func(argc, process->argv, STDOUT_FILENO);
		close(process->io_buffer[STDIN_FILENO]);
		close(process->io_buffer[STDOUT_FILENO]);
	}
	return (pid);
}
