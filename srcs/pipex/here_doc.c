/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 16:07:00 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/09/11 19:36:44 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

// Read here_doc input and write it to "here_doc" file.
// Return "here_doc"s fd
int	here_doc(void)
{
	int		here_doc_fd;
	int		val;
	char	endl;
	char	*line;
	char	*stop_word;

	here_doc_fd = open(HERE_DOC, O_WRONLY | O_TRUNC | O_CREAT, 0600);
	if (here_doc_fd < 0)
		return (-1);
	stop_word = readline("stop_word: ");
	endl = '\n';
	while (1)
	{
		line = readline("> ");
		if (cmp_strings(line, stop_word))
		{
			free(line);
			break ;
		}
		write(here_doc_fd, line, ft_strlen(line));
		write(here_doc_fd, &endl, 1);
		free(line);
	}
	return (open(HERE_DOC, O_RDONLY));
}
