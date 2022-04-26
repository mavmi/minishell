/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_here_doc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 16:07:00 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/12/19 17:57:09 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/processes.h"

static void	exit_here_doc(int sig)
{
	(void)sig;
	printf("\n");
	exit(1);
}

static int	here_doc_func(char *stop_word, int out_fd)
{
	char	*line;

	if (!stop_word)
		return (1);
	while (1)
	{
		line = readline("> ");
		if (!line)
			return (0);
		if (utils_cmp_strings(line, stop_word))
		{
			free(line);
			return (0);
		}
		write(out_fd, line, ft_strlen(line));
		write(out_fd, "\n", 1);
		free(line);
	}
}

static pid_t	exec_here_doc(char *stop_word, int in_fd, int out_fd)
{
	int		exit_code;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		close(in_fd);
		close(out_fd);
	}
	par_disable_sig();
	if (pid == 0)
	{
		rl_catch_signals = 1;
		par_set_default_sig();
		signal(SIGINT, exit_here_doc);
		close(in_fd);
		exit_code = here_doc_func(stop_word, out_fd);
		close(out_fd);
		free(stop_word);
		exit(exit_code);
	}
	return (pid);
}

// Read here_doc input, write it to the pipe and
// return it's fd.
// Return fd to read line from
// or -1 if an error occured.
int	proc_here_doc(char *stop_word)
{
	pid_t	pid;
	int		io_buffer[2];

	if (pipe(io_buffer))
		return (NON_FD);
	pid = exec_here_doc(stop_word, io_buffer[STDIN_FILENO],
			io_buffer[STDOUT_FILENO]);
	if (!pid)
		return (NON_FD);
	waitpid(pid, &g_data.exit_status, WNOHANG & WUNTRACED);
	if (WIFEXITED(g_data.exit_status))
		g_data.exit_status = WEXITSTATUS(g_data.exit_status);
	par_set_custom_sig();
	close(io_buffer[STDOUT_FILENO]);
	free(stop_word);
	if (g_data.exit_status == 0)
		return (io_buffer[STDIN_FILENO]);
	close(io_buffer[STDIN_FILENO]);
	return (NON_HERE_DOC);
}
