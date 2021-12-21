/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 18:11:25 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/12/21 16:42:44 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/processes.h"

int	proc_open_file_(char *path, t_file_mode file_mode)
{
	int	fd;

	if (!path)
		fd = NON_FD;
	if (file_mode == READ)
		fd = open(path, O_RDONLY);
	else if (file_mode == WRITE)
		fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0700);
	else if (file_mode == WRITE_APP)
		fd = open(path, O_WRONLY | O_CREAT | O_APPEND, 0700);
	else if (file_mode == READ_WRITE)
		fd = open(path, O_RDWR);
	else if (file_mode == READ_WRITE_APP)
		fd = open(path, O_RDWR | O_TRUNC);
	else
		fd = NON_FD;
	if (fd < 0)
		g_data.exit_status = 1;
	else
		g_data.exit_status = 0;
	return (fd);
}

// Open file with specified mode
int	proc_open_file(char *path, t_file_mode file_mode)
{
	int	fd;

	fd = proc_open_file_(path, file_mode);
	free(path);
	return (fd);
}
