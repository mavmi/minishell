/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_fd_array.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalena <msalena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 18:38:55 by msalena           #+#    #+#             */
/*   Updated: 2021/12/05 17:20:36 by msalena          ###   ########.fr       */
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
		len = fd_arr_len(fd_arr);
	new_arr = (int *)malloc(sizeof(int) * (len + 3));
	if (!new_arr)
	{
		free(fd_arr);
		return (NULL);
	}
	while (fd_arr && fd_arr[i] != END_OF_FD_ARR)
	{
		new_arr[i] = fd_arr[i];
		i++;
	}
	free(fd_arr);
	new_arr[i] = in_fd;
	new_arr[++i] = out_fd;
	new_arr[++i] = -2;
	return (new_arr);
}

static void	mistake_fd(int fd, char *error)
{
	char	*error_str;

	error_str = NULL;
	if (fd == NON_FD)
	{
		if (utils_cmp_strings(error, "here_doc") == 1)
			error_str = utils_sum_strings("minishell: here_doc",
					strerror(errno));
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

static t_par_elem	*between_pipe(t_par_elem *sub, int *fd_in, int *fd_out)
{
	if (sub && sub->type == OPER_HERE_DOC_N)
	{
		sub = sub->next;
		*fd_in = proc_here_doc(delets_spaces(sub->value));
		mistake_fd(*fd_in, "here_doc");
	}
	else if (sub && sub->type == OPER_INP_N && sub->type != DEFAULT_N
		&& sub->type != OPER_DOLL_N)
	{
		*fd_in = proc_open_file(delets_spaces(sub->next->value), READ);
		mistake_fd(*fd_in, sub->next->value);
	}
	else if (sub && sub->type != DEFAULT_N
		&& sub->type != OPER_DOLL_N)
	{
		if (sub && (sub->type == OPER_OUT_N))
			*fd_out = proc_open_file(delets_spaces(sub->next->value), WRITE);
		else if (sub && (sub->type == OPER_OUT_APP_N))
			*fd_out = proc_open_file(delets_spaces(sub->next->value),
					WRITE_APP);
		mistake_fd(*fd_out, sub->next->value);
	}
	return (sub);
}

int	*arr_fd_formation(t_par_elem *sub)
{
	int	*fd_arr;
	int	fd_input;
	int	fd_output;

	if (!sub)
		return (NULL);
	fd_input = 0;
	fd_output = 1;
	fd_arr = NULL;
	while (sub)
	{
		if (sub->type == OPER_PIPE_N || !sub->next)
		{
			fd_arr = arr_fd_add_realloc(fd_arr, fd_input, fd_output);
			if (!fd_arr)
				return (NULL);
			fd_input = 0;
			fd_output = 1;
		}
		else if (sub && sub->type != DEFAULT_N
			&& sub->type != OPER_DOLL_N)
			sub = between_pipe(sub, &fd_input, &fd_output);
		sub = sub->next;
	}
	return (fd_arr);
}
