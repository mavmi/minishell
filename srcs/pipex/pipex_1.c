/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 19:04:40 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/11/10 14:03:36 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

// Parh of proc_get_new_elem function.
// Return 0 if everything is ok,
// 1 otherwise
static int	proc_get_new_elem_handler(t_process *proc, char **argv, char **dirs)
{
	if (!proc || !argv || !dirs)
		return (1);
	proc->next = NULL;
	proc->prev = NULL;
	proc->exec_path = NULL;
	proc->argv = argv;
	proc->exec_name = ft_strdup(argv[0]);
	if (rebuit_is_rebuilt(argv[0]))
		proc->is_default = 0;
	else
		proc->is_default = 1;
	if (proc->is_default)
		proc->exec_path = proc_find_executable(dirs, argv[0]);
	if (!proc->exec_name || (proc->is_default && !proc->exec_path))
		return (1);
	return (0);
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
		utils_destroy_strings_array(argv);
		return (NULL);
	}
	if (proc_get_new_elem_handler(process, argv, dirs))
	{
		proc_destroy_elem(process);
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
		utils_destroy_strings_array(dirs);
		proc_destroy_elem(list);
		return (NULL);
	}
	proc_init_list_handler(&list, commands, dirs);
	utils_destroy_strings_array(dirs);
	return (list);
}
