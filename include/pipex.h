/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 18:41:09 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/11/12 14:13:02 by pmaryjo          ###   ########.fr       */
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
typedef struct s_here_doc	t_here_doc;

struct s_process
{
	pid_t		pid;
	int			is_built_in;
	int			io_buffer[2];
	char		*exec_name;
	char		*exec_path;
	char		**argv;
	t_process	*next;
	t_process	*prev;
};

t_process	*proc_get_new_elem(char *command, char **dirs);
t_process	*proc_init_list(char **commands, char **envp);

void		proc_execute_list(t_process *list, int input, int output);

pid_t		process_execute_built_in(t_process *process, int in, int out);
pid_t		process_execute_rebuilt(t_process *process, int out);

void		proc_destroy_elem(t_process *process);
void		proc_destroy_list(t_process *list);

char		**proc_get_paths_array(char **envp);
char		*proc_find_executable(char **dirs, char *file_name);

int			proc_open_input_file(char *file_path);
int			proc_open_output_file(char *file_path);

int			proc_here_doc(void);

#endif
