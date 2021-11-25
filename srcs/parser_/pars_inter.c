/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_inter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 15:52:01 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/11/25 16:13:49 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser_.h"

static char	**proc_get_dirs(void)
{
	char	**envp;

	envp = env_get_content(g_data.envp);
	if (!envp)
		return (NULL);
	return (proc_get_paths_array(envp));	
}

// Convert parser list to process list.
// May return NULL
t_process	*proc_intepret(t_pars_list *pars_list)
{
	char		*cmd;
	char		**dirs;
	t_process	*proc_list;

	if (!pars_list)
		return (NULL);
	proc_list = NULL;
	dirs = proc_get_dirs();
	if (!dirs)
		return (NULL);
	while (pars_list)
	{		
		if (pars_list->type == DEFAULT_N)
		{
			utils_append_string(&cmd, pars_list->value);
			if (!cmd)
			{
				proc_destroy_list(proc_list);
				return (NULL);
			}
		}
		else if (pars_list->type == REDIR_OUT_N
			|| pars_list->type == REDIR_OUT_APP_N)
		{
			// Взять название файла из следующего элемента парс_листа
			// и положить его в output элемента проц_листа.
			// Не забыть про флаг аппенда
		}
		else if (pars_list->type == REDIR_INP_N)
		{
			// Взять название файла из следующего элемента парс_листа
			// и положить его в input элемента проц_листа.
		}
		else if (pars_list->type == HERE_DOC_N)
		{
			// Вызвать хер_док и сохранить его дескриптор
			// в элемент проц_листа
		}
		else if (pars_list->type == PIPE_N)
		{
			// Добавить парс_элемент в список и создать новый элемент
		}
	}
	return (proc_list);
}
