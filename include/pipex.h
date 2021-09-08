/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 18:41:09 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/09/08 19:07:05 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>

# include "../libft/libft.h"
# include "utils.h"

typedef struct s_process	t_process;

struct s_process
{
	int			output[2];
	size_t		num;
	char		*exec_name;
	char		*exec_path;
	char		**argv;
	t_process	*next;
	t_process	*prev;
};

char		*proc_find_executable(char **dirs, char *file_name);
char		**proc_get_paths_array(char **envp);
void		proc_destroy_elem(t_process *process);
void		proc_destroy_list(t_process *list);
t_process	*proc_get_new_elem(char *command, char **dirs);
t_process	*proc_init_list(char **commands, char **envp);
void		proc_execute_list(t_process *list);

#endif
