/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_inter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 15:52:01 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/11/26 18:49:08 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser_.h"

static char	**proc_get_dirs(void)
{
	char	**dirs;
	char	**envp;

	envp = env_get_content(g_data.envp);
	dirs = proc_get_paths_array(envp);
	utils_destroy_strings_array(envp);
	return (dirs);	
}

// Convert parser list to process list.
// May return NULL
t_process	*pars_intepret(t_pars_list *pars_list)
{
	int			type;
	int			in_fd;
	int			out_fd;
	char		*cmd;
	char		**dirs;
	t_process	*elem;
	t_process	*proc_list;

	if (!pars_list)
		return (NULL);
	dirs = proc_get_dirs();
	if (!dirs)
		return (NULL);
	cmd = NULL;
	in_fd = NON_FD;
	out_fd = NON_FD;
	proc_list = NULL;
	while (pars_list)
	{		
		if (pars_list->type == DEFAULT_N)
		{
			utils_append_string(&cmd, " ");
			utils_append_string(&cmd, pars_list->value);
			if (!cmd)
			{
				proc_destroy_list(proc_list);
				return (NULL);
			}
		}
		if (pars_list->type == REDIR_OUT_N
			|| pars_list->type == REDIR_OUT_APP_N)
		{
			type = pars_list->type;
			pars_list = pars_list->next;
			if (type == REDIR_OUT_N)
				out_fd = open(pars_list->value, O_WRONLY | O_CREAT, 0700);
			else
				out_fd = open(pars_list->value, O_WRONLY | O_TRUNC | O_CREAT, 0700);
		}
		if (pars_list->type == REDIR_INP_N)
		{
			pars_list = pars_list->next;
			in_fd = open(pars_list->value, O_RDONLY);
		}
		if (pars_list->type == HERE_DOC_N)
		{
			pars_list = pars_list->next;
			in_fd = proc_here_doc(pars_list->value);
		}
		if (pars_list->type == PIPE_N || pars_list->next == NULL)
		{
			elem = proc_get_new_elem(cmd, in_fd, out_fd);
			proc_push_back(&proc_list, elem);
			free(cmd);
			cmd = NULL;
			in_fd = NON_FD;
			out_fd = NON_FD;
		}
		pars_list = pars_list->next;
	}
	utils_destroy_strings_array(dirs);
	return (proc_list);
}
