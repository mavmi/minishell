/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_inter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 15:52:01 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/11/27 14:51:11 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser_.h"

// Append commande with list's value and
// return 0 if everything is ok,
// 1 otherwise
static int	pars_append_cmd(char **cmd, t_pars_list *pars_list)
{
	utils_append_string(cmd, " ");
	utils_append_string(cmd, pars_list->value);
	if (!*cmd)
		return (1);
	return (0);
}

static void	pars_redirect(t_pars_list **pars_list, int *in_fd, int *out_fd)
{
	int	type;

	type = (*pars_list)->type;
	(*pars_list) = (*pars_list)->next;
	if (type == REDIR_OUT)
		*out_fd = open((*pars_list)->value,
				O_WRONLY | O_CREAT | O_TRUNC, 0700);
	else if (type == REDIR_OUT_APP)
		*out_fd = open((*pars_list)->value,
				O_WRONLY | O_CREAT | O_APPEND, 0700);
	else if (type == REDIR_INP)
		*in_fd = open((*pars_list)->value, O_RDONLY);
	else if (type == HERE_DOC_)
		*in_fd = proc_here_doc((*pars_list)->value);
}

static void	pars_pipe(t_process **proc_list, char **cmd,
		int *in_fd, int *out_fd)
{
	t_process	*proc_elem;

	proc_elem = proc_get_new_elem(*cmd, *in_fd, *out_fd);
	proc_push_back(proc_list, proc_elem);
	free(*cmd);
	*cmd = NULL;
	*in_fd = NON_FD;
	*out_fd = NON_FD;
}

static t_process	*pars_kostil(t_process *proc_list)
{
	proc_destroy_list(proc_list);
	return (NULL);
}

// Convert parser list to process list.
// May return NULL
t_process	*pars_intepret(t_pars_list *pars_list)
{
	int			in_fd;
	int			out_fd;
	char		*cmd;
	t_process	*proc_list;

	if (!pars_list)
		return (NULL);
	cmd = NULL;
	in_fd = NON_FD;
	out_fd = NON_FD;
	proc_list = NULL;
	while (pars_list)
	{		
		if (pars_list->type == DEFAULT && pars_append_cmd(&cmd, pars_list))
			return (pars_kostil(proc_list));
		if (pars_list->type == REDIR_OUT || pars_list->type == REDIR_OUT_APP
			|| pars_list->type == REDIR_INP || pars_list->type == HERE_DOC_)
			pars_redirect(&pars_list, &in_fd, &out_fd);
		if (pars_list->type == PIPE || pars_list->next == NULL)
			pars_pipe(&proc_list, &cmd, &in_fd, &out_fd);
		pars_list = pars_list->next;
	}
	return (proc_list);
}
