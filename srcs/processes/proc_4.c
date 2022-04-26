/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 17:47:31 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/12/15 14:02:09 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/processes.h"

// STDIN_FILENO = 0
// STDOUT_FILENO = 1
// pipe[0] -> read
// pipe[1] -> write
static void	proc_redirect(t_process *proc, int input, int output)
{
	if (input != STDIN_FILENO)
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
	if (output != STDOUT_FILENO)
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

// Execute one built-in process and return it's PID
pid_t	process_execute_built_in(t_process *process)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		perror(strerror(errno));
	if (pid == 0)
	{
		par_set_default_sig();
		proc_redirect(process, process->input_fd, process->output_fd);
		if (execve(process->exec_path, process->argv,
				env_get_content(g_data.envp, 0)) == -1)
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(process->exec_name, STDERR_FILENO);
			ft_putstr_fd(": ", STDERR_FILENO);
			ft_putendl_fd(strerror(errno), STDERR_FILENO);
			exit(BAD_STATUS);
		}
	}
	return (pid);
}

// Part of process_execute_rebuilt function
static void	process_execute_rebuilt_handler(t_process *process, int argc)
{
	if (process->output_fd != STDOUT_FILENO)
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

// Execute one rebuilt process
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
