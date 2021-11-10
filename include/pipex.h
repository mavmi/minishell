/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 18:41:09 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/11/10 14:05:42 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define HERE_DOC "here_doc"

# include <stdlib.h>
# include <unistd.h>
# include <sys/errno.h>

# include "../libft/libft.h"
# include "utils.h"
# include "rebuilt_funcs.h"
# include "enviroment.h"

# define BAD_STATUS 1

typedef struct s_process	t_process;

struct s_process
{
	pid_t		pid;
	int			is_default;
	int			io_buffer[2];
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

void		proc_execute_default_func(t_process *proc,
				int input, int output);
void		proc_execute_list(t_process *list, int input, int output);

int			proc_open_input_file(char *file_path);
int			proc_open_output_file(char *file_path);

int			here_doc(void);

#endif
