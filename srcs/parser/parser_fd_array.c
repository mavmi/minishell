/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_fd_array.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalena <msalena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 18:38:55 by msalena           #+#    #+#             */
/*   Updated: 2021/12/05 14:58:34 by msalena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

static int	fd_arr_len(int *fd_arr)
{
	int	size;

	if (!fd_arr)
		return (0);
	size = 0;
	while (fd_arr[size] != -2)
		size++;
	return (size);
}

static int	*arr_fd_add_realloc(int *fd_arr, int in_fd, int out_fd)
{
	int	*new_arr;
	int	len;
	int	i;

	len = 0;
	i = 0;
	if (fd_arr)
		len = fd_arr_len(fd_arr);
	new_arr = (int *)malloc(sizeof(int) * (len + 3));
	if (!new_arr)
	{
		if (fd_arr)
			free(fd_arr);
		return (NULL);
	}
	while (fd_arr && fd_arr[i] != END_OF_FD_ARR)
	{
		new_arr[i] = fd_arr[i];
		i++;
	}
	if (fd_arr)
		free(fd_arr);
	new_arr[i] = in_fd;
	new_arr[++i] = out_fd;
	new_arr[++i] = -2;
	return (new_arr);
}

static void	mistake_fd(int fd, char *error)
{
	char *error_str;

	error_str = NULL;
	if (fd == NON_FD)
	{
		if (utils_cmp_strings(error, "here_doc") == 1)
			error_str = utils_sum_strings("minishell: here_doc", strerror(errno));
		else
		{
			error_str = utils_sum_strings("minishell: ", error);
			utils_append_string(&error_str, ": ");
			utils_append_string(&error_str, strerror(errno));
		}
	ft_putendl_fd(error_str, STDERR_FILENO);
	}
	free(error_str);
}

static char	*delets_spaces(char *list_elem)
{
	int	i;

	i = 0;
	while (list_elem[i])
		i++;
	i--;
	if (list_elem[i] == ' ')
	{
		while (i && list_elem[i] == ' ')
			i--;
		list_elem[++i] = '\0';
	}
	return (list_elem);
}

int	*arr_fd_formation(t_par_list *elem_list)
{
	t_par_elem	*substr;
	int	*fd_arr;
	int	fd_input;
	int	fd_output;

	if (!elem_list)
		return(NULL);
	substr = elem_list->begin;
	fd_input = 0; // maybe needs changing default fd
	fd_output = 1; // maybe needs changing default fd
	fd_arr = NULL;
	while (substr)
	{
		if (substr->type == OPER_PIPE_N || !substr->next)
		{
			fd_arr = arr_fd_add_realloc(fd_arr, fd_input, fd_output);
			if (!fd_arr)
				return(NULL);
			fd_input = 0;
			fd_output = 1;
		}
		else if (substr && substr->type == OPER_HERE_DOC_N)
		{
			substr = substr->next;
			fd_input = proc_here_doc(delets_spaces(substr->value));
			mistake_fd(fd_input, "here_doc");
		}
		else if (substr && substr->type != DEFAULT_N && substr
									&& substr->type != OPER_DOLL_N)
		{
			if (substr && substr->type == OPER_INP_N)
            {
                fd_input = proc_open_file(delets_spaces(substr->next->value), READ);
                mistake_fd(fd_input, substr->next->value);
            }
            else
            {
                if (substr && (substr->type == OPER_OUT_N))
                    fd_output = proc_open_file(delets_spaces(substr->next->value), WRITE);
                else if (substr && (substr->type == OPER_OUT_APP_N))
                    fd_output = proc_open_file(delets_spaces(substr->next->value), WRITE_APP);
                mistake_fd(fd_output, substr->next->value);
            }
		}
		substr = substr->next;
	}
	return (fd_arr);
}
