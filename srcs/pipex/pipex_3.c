/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 17:36:19 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/11/26 18:14:33 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

// STDIN_FILENO = 0
// STDOUT_FILENO = 1
// pipe[0] -> read
// pipe[1] -> write
static void	proc_redirect(t_process *proc, int input, int output)
{
	if (input != STDIN_FILENO && input != NON_FD)
	{
		dup2(input, STDIN_FILENO);
		close(input);
	}
	else if (proc->prev)
	{
		dup2(proc->prev->io_buffer[STDIN_FILENO], STDIN_FILENO);
		close(proc->prev->io_buffer[STDIN_FILENO]);
		close(proc->prev->io_buffer[STDOUT_FILENO]);
	}
	if (output != STDOUT_FILENO && output != NON_FD)
	{
		dup2(output, STDOUT_FILENO);
		close(output);
	}
	else if (proc->next)
	{
		dup2(proc->io_buffer[STDOUT_FILENO], STDOUT_FILENO);
		close(proc->io_buffer[STDIN_FILENO]);
		close(proc->io_buffer[STDOUT_FILENO]);
	}
}

pid_t	process_execute_built_in(t_process *process)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		perror(strerror(errno));
	if (pid == 0)
	{
		proc_redirect(process, process->input_fd, process->output_fd);
		if (execve(process->exec_path, process->argv,
				env_get_content(g_data.envp)) == -1)
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

static void	process_execute_rebuilt_handler(t_process *process, int argc)
{
	if (process->output_fd != NON_FD)
	{
		rebuilt_call_func(argc, process->argv, process->output_fd);
		close(process->io_buffer[STDIN_FILENO]);
		close(process->io_buffer[STDOUT_FILENO]);
		close(process->output_fd);
	}
	else if (!process->next)
	{
		rebuilt_call_func(argc, process->argv, STDOUT_FILENO);
		close(process->io_buffer[STDIN_FILENO]);
		close(process->io_buffer[STDOUT_FILENO]);
	}
	else
	{
		rebuilt_call_func(argc, process->argv,
			process->io_buffer[STDOUT_FILENO]);
		close(process->io_buffer[STDOUT_FILENO]);
	}
}

void	process_execute_rebuilt(t_process *process)
{
	int		argc;
	char	**ptr;

	argc = 0;
	ptr = process->argv;
	while (*ptr)
	{
		ptr++;
		argc++;
	}
	process_execute_rebuilt_handler(process, argc);
}
