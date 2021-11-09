/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 19:04:40 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/11/09 18:47:49 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

// Fill process element with default values and parsed command
// to execute built-in function
static void	proc_fill_default(t_process **process, char **argv, char **dirs)
{
	if (!*process || !argv || !dirs)
		return ;
	(*process)->is_default = 1;
	(*process)->next = NULL;
	(*process)->prev = NULL;
	(*process)->argv = argv;
	(*process)->exec_name = ft_strdup((*process)->argv[0]);
	(*process)->exec_path = proc_find_executable(dirs, (*process)->argv[0]);
	if (!(*process)->exec_name || !(*process)->exec_path)
	{
		proc_destroy_elem(*process);
		*process = NULL;
	}
}

// Fill process element with default values and parsed command
// to execute rebuild function (echo, pwd etc.)
static void	proc_fill_rebuild(t_process **process, char **argv)
{
	if (!*process || !argv)
		return ;
	(*process)->is_default = 0;
	(*process)->exec_name = ft_strdup(argv[0]);
	(*process)->exec_path = NULL;
	(*process)->next = NULL;
	(*process)->prev = NULL;
	(*process)->argv = argv;
	if (!(*process)->exec_name)
	{
		proc_destroy_elem(*process);
		*process = NULL;
	}
}

// Create new t_process struct.
// May return NULL
t_process	*proc_get_new_elem(char *command, char **dirs)
{
	char		**argv;
	t_process	*process;

	if (!command || !dirs)
		return (NULL);
	process = (t_process *)malloc(sizeof(t_process));
	argv = ft_split(command, ' ');
	if (!process || !argv)
	{
		free(process);
		destroy_strings_array(argv);
		return (NULL);
	}
	if (is_rebuild(argv[0]))
		proc_fill_rebuild(&process, argv);
	else
		proc_fill_default(&process, argv, dirs);
	if (!process)
	{
		destroy_strings_array(argv);
		return (NULL);
	}
	return (process);
}

// Part of proc_init_list function
static void	proc_init_list_handler(t_process **list, char **cmds, char **dirs)
{
	t_process	*ptr;
	t_process	*new_elem;

	if (!list || !cmds || !dirs)
		return ;
	ptr = *list;
	while (*cmds)
	{
		new_elem = proc_get_new_elem(*cmds++, dirs);
		if (!new_elem || pipe(new_elem->io_buffer))
		{
			proc_destroy_list(*list);
			*list = NULL;
			return ;
		}
		ptr->next = new_elem;
		new_elem->prev = ptr;
		ptr = new_elem;
	}
}

// Parse commands to create list of processes to execute.
// May return NULL
t_process	*proc_init_list(char **commands, char **envp)
{
	t_process	*list;
	char		**dirs;

	if (!commands || !envp)
		return (NULL);
	dirs = proc_get_paths_array(envp);
	if (!dirs)
		return (NULL);
	list = proc_get_new_elem(*commands++, dirs);
	if (!list || pipe(list->io_buffer))
	{
		destroy_strings_array(dirs);
		proc_destroy_elem(list);
		return (NULL);
	}
	proc_init_list_handler(&list, commands, dirs);
	destroy_strings_array(dirs);
	return (list);
}
