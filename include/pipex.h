/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 18:41:09 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/09/06 19:06:01 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>

# include "../libft/libft.h"

typedef struct s_process	t_process;

struct s_process
{
	int			fields[2];
	char		*exec_name;
	char		*exec_path;
	char		**argv;
	t_process	*next;
};

char	*find_executable(char **dirs, char *file_name);

#endif
