/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_here_doc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 16:07:00 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/12/12 13:49:32 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/processes.h"

static int	proc_here_doc_(char *stop_word)
{
	int		io_buffer[2];
	char	*line;

	if (!stop_word || pipe(io_buffer))
		return (NON_FD);
	while (1)
	{
		line = readline("> ");
		if (!line)
			return (NON_HERE_DOC);
		if (utils_cmp_strings(line, stop_word))
		{
			free(line);
			close(io_buffer[STDOUT_FILENO]);
			return (io_buffer[STDIN_FILENO]);
		}
		write(io_buffer[STDOUT_FILENO], line, ft_strlen(line));
		write(io_buffer[STDOUT_FILENO], "\n", 1);
		free(line);
	}
}

// Read here_doc input, write it to the pipe and
// return it's fd.
// Return fd to read line from
// or -1 if an error occured.
int	proc_here_doc(char *stop_word)
{
	int	fd;

	fd = proc_here_doc_(stop_word);
	free(stop_word);
	return (fd);
}
