/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalena <msalena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 18:11:25 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/12/05 14:56:37 by msalena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/processes.h"

// Open file with specified mode
int	proc_open_file(char *path, t_file_mode file_mode)
{
	// printf("p = %s|\n", path);
	if (!path)
		return (NON_FD);
	if (file_mode == READ)
		return (open(path, O_RDONLY));
	else if (file_mode == WRITE)
		return (open(path, O_WRONLY | O_CREAT | O_TRUNC, 0700));
	else if (file_mode == WRITE_APP)
		return (open(path, O_WRONLY | O_CREAT | O_APPEND, 0700));
	else if (file_mode == READ_WRITE)
		return (open(path, O_RDWR));
	else if (file_mode == READ_WRITE_APP)
		return (open(path, O_RDWR | O_TRUNC));
	return (NON_FD);
}
