/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 19:04:40 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/11/09 16:51:48 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

void	proc_destroy_elem(t_process *process)
{
	if (!process)
		return ;
	free(process->exec_name);
	free(process->exec_path);
	destroy_strings_array(process->argv);
	free(process);
}

void	proc_destroy_list(t_process *list)
{
	t_process	*tmp_ptr;

	if (!list)
		return ;
	while (list)
	{
		tmp_ptr = list->next;
		proc_destroy_elem(list);
		list = tmp_ptr;
	}
}

// Create new t_process struct.
// May return NULL
t_process	*proc_get_new_elem(char *command, char **dirs)
{
	t_process	*process;

	if (!command || !dirs)
		return (NULL);
	process = (t_process *)malloc(sizeof(t_process));
	if (!process)
		return (NULL);
	process->exec_name = NULL;
	process->exec_path = NULL;
	process->next = NULL;
	process->prev = NULL;
	process->argv = ft_split(command, ' ');
	if (!process->argv)
	{
		free(process);
		return (NULL);
	}
	process->exec_name = ft_strdup(process->argv[0]);
	process->exec_path = proc_find_executable(dirs, process->argv[0]);
	if (!process->exec_name || !process->exec_path)
	{
		proc_destroy_elem(process);
		return (NULL);
	}
	return (process);
}

// Part of proc_init_list function
static t_process	*proc_init_list_handler(char **commands, char **dirs)
{
	t_process	*list;
	t_process	*ptr;
	t_process	*new_elem;

	list = proc_get_new_elem(*commands++, dirs);
	if (!list)
		return (NULL);
	pipe(list->io_buffer);
	ptr = list;
	while (*commands)
	{
		new_elem = proc_get_new_elem(*commands++, dirs);
		if (!new_elem)
		{
			proc_destroy_elem(list);
			return (NULL);
		}
		pipe(ptr->io_buffer);
		ptr->next = new_elem;
		new_elem->prev = ptr;
		ptr = new_elem;
	}
	return (list);
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
	list = proc_init_list_handler(commands, dirs);
	destroy_strings_array(dirs);
	return (list);
}
