/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 19:04:40 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/11/26 16:03:48 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

// Parh of proc_get_new_elem function.
// Return 0 if everything is ok,
// 1 otherwise
static int	proc_get_new_elem_handler(t_process *proc, char **argv)
{
	if (!proc || !argv)
		return (1);
	proc->next = NULL;
	proc->prev = NULL;
	proc->exec_path = NULL;
	proc->argv = argv;
	proc->exec_name = ft_strdup(argv[0]);
	if (rebuit_is_rebuilt(argv[0]))
		proc->is_built_in = 0;
	else
		proc->is_built_in = 1;
	if (proc->is_built_in)
		proc->exec_path = proc_parse_cmd(argv[0]);
	if (!proc->exec_name || (proc->is_built_in && !proc->exec_path))
		return (1);
	return (0);
}

// Create new t_process struct.
// May return NULL
// command = "[cmd] {arg_1} ... {arg_n}" - may not contain arguments
t_process	*proc_get_new_elem(char *cmd, int in, int out)
{
	char		**argv;
	t_process	*process;

	if (!cmd)
		return (NULL);
	process = (t_process *)malloc(sizeof(t_process));
	argv = ft_split(cmd, ' ');
	if (!process || !argv)
	{
		free(process);
		utils_destroy_strings_array(argv);
		return (NULL);
	}
	if (proc_get_new_elem_handler(process, argv))
	{
		proc_destroy_elem(process);
		return (NULL);
	}
	process->input_fd = in;
	process->output_fd = out;
	return (process);
}

// Part of proc_init_list function
static void	proc_init_list_handler(t_process **list, char **cmds)
{
	t_process	*ptr;
	t_process	*new_elem;

	if (!list || !cmds)
		return ;
	ptr = *list;
	while (*cmds)
	{
		new_elem = proc_get_new_elem(*cmds++, NON_FD, NON_FD);
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

	if (!commands || !envp)
		return (NULL);
	list = proc_get_new_elem(*commands++, NON_FD, NON_FD);
	if (!list || pipe(list->io_buffer))
	{
		proc_destroy_elem(list);
		return (NULL);
	}
	proc_init_list_handler(&list, commands);
	return (list);
}

void	proc_push_back(t_process **list, t_process *elem)
{
	t_process	*ptr;

	if (!list || !elem)
		return ;
	if (!*list)
	{
		*list = elem;
		return ;
	}
	ptr = *list;
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = elem;
}
