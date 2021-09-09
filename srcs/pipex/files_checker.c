/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 18:11:25 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/09/09 18:19:49 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

// Open file input [file_path] and return it's fd
int	proc_open_input_file(char *file_path)
{
	if (access(file_path, R_OK) == -1)
	{
		perror(strerror(errno));
		return (-1);
	}
	return (open(file_path, O_RDONLY));
}

// Open file output [file_path] or create it
// and return it's fd
int	proc_open_output_file(char *file_path)
{
	if (!access(file_path, W_OK))
		return (open(file_path, O_WRONLY | O_TRUNC));
	else if (!access(file_path, F_OK))
	{
		perror(strerror(errno));
		return (-1);
	}
	return (open(file_path, O_WRONLY | O_CREAT, 0700));
}
