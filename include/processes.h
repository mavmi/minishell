/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 18:41:09 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/12/15 16:48:09 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESSES_H
# define PROCESSES_H

# define HERE_DOC "here_doc"

# include <stdlib.h>
# include <unistd.h>
# include <sys/errno.h>

# include "../libft/libft.h"
# include "utils.h"
# include "rebuilt_funcs.h"
# include "enviroment.h"
# include "parser.h"

# define BAD_STATUS 1
# define NON_FD -1
# define NON_HERE_DOC -2

typedef enum e_file_mode	t_file_mode;
typedef struct s_process	t_process;

enum e_file_mode
{
	READ,
	WRITE,
	WRITE_APP,
	READ_WRITE,
	READ_WRITE_APP
};

struct s_process
{
	pid_t		pid;
	int			is_built_in;
	int			input_fd;
	int			output_fd;
	int			io_buffer[2];
	char		*exec_name;
	char		*exec_path;
	char		**argv;
	t_process	*next;
	t_process	*prev;
};

// proc_1.c
t_process	*proc_get_new_elem(char *cmd, int in, int out);
t_process	*proc_init_list(char **cmd, int *fd, char **envp);

// proc_2.c
void		proc_destroy_elem(t_process *process);
void		proc_destroy_list(t_process *list);

// proc_3.c
void		proc_execute_list(t_process *list);

// proc_4.c
pid_t		process_execute_built_in(t_process *process);
void		process_execute_rebuilt(t_process *process);

// proc_paths.c
char		**proc_get_paths_array(char **envp);
char		*proc_parse_cmd(char *cmd);

// proc_files.c
int			proc_open_file(char *path, t_file_mode file_mode);

// proc_here_doc.c
int			proc_here_doc(char *stop_word);

// proc_split.c
char		**proc_split(char *cmd);

#endif
