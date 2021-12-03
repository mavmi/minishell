/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_fd_array.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 18:38:55 by msalena           #+#    #+#             */
/*   Updated: 2021/12/03 15:56:51 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

static int	*arr_fd_add_realloc(int *fd_arr, int in_fd, int out_fd)
{
	int	*new_arr;
	int	len;
	int	i;

	len = 0;
	i = 0;
	if (fd_arr)
		len = ft_strlen((int *)fd_arr);
	new_arr = (int *)malloc(sizeof(int) * (len + 3));
	if (!new_arr)
		return (NULL);
	while (fd_arr && fd_arr[i])
	{
		new_arr[i] = fd_arr[i];
		i++;
	}
	if (fd_arr)
		free(fd_arr);
	new_arr[i] = in_fd;
	new_arr[++i] = out_fd;
	new_arr[++i] = '\0';
	return (new_arr);
}

int	*arr_fd_formation(t_par_list *elem_list)
{
	t_par_elem	*substr;
	int	*fd_arr;
	size_t	fl_start;
	int	fd_input;
	int	fd_output;
	char *error_str;

	substr = elem_list->begin;
	fd_input = 0; // maybe needs changing default fd
	fd_output = 1; // maybe needs changing default fd
	fl_start = 0;
	fd_arr = NULL;
	error_str = NULL;
	while (substr)
	{
		if (substr->type == OPER_PIPE_N)
		{
			fd_arr = arr_fd_add_realloc(fd_arr, in_fd, out_fd);
			fl_start = substr->number_pos;
			substr = substr->next;
		}
		else if (substr && substr->type == OPER_HERE_DOC_N)
		{
			substr = substr->next;
			fd_input = proc_here_doc(substr->value);
			///////////////mistakes/////////////
			if (fd_input == -1)
			{
				if ((par_get_by_pos(elem_list, (fl_start + 1))->type == DEFAULT_N)
				{
					error_str = utils_sum_strings("minishell: ",
										par_get_by_pos(elem_list, (fl_start + 1))->value); // minishell: "filename"
				}
				else
				{
					error_str = utils_sum_strings("minishell: ",
										par_get_by_pos(elem_list, (fl_start + 2))->value); // minishell: "filename"
				}
				utils_append_string(&error_str, ":");// minishell: "filename":
				utils_append_string(&error_str, strerror(errno)); // minishell: "filename": strerror(errno)
				ft_putendl_fd(error_str, 1);
			}
			///////////////////////////////////
		}
		else if (substr && substr->type == OPER_INP_N)
		{

		}
		else if (substr && (substr->type == OPER_OUT_N
								|| substr->type == OPER_OUT_APP_N))
		{

		}
		substr = substr->next;
	}


}
