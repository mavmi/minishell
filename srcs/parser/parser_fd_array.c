/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_fd_array.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 18:38:55 by msalena           #+#    #+#             */
/*   Updated: 2021/12/18 16:20:33 by pmaryjo          ###   ########.fr       */
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
	new_arr[++i] = END_OF_FD_ARR;
	return (new_arr);
}

static int	mistake_fd(int fd, char *error)
{
	char	*parsed;
	char	*error_str;

	error_str = NULL;
	if (fd == NON_HERE_DOC)
		return (NON_HERE_DOC);
	if (fd == NON_FD)
	{
		parsed = par_parse_quotes_and_vars(error, 1);
		if (utils_cmp_strings(parsed, "here_doc") == 1)
			error_str = utils_sum_strings("minishell: here_doc: ",
					strerror(errno));
		else
		{
			error_str = utils_sum_strings("minishell: ", parsed);
			utils_append_string(&error_str, ": ");
			utils_append_string(&error_str, strerror(errno));
		}
		free(parsed);
		ft_putendl_fd(error_str, STDERR_FILENO);
	}
	free(error_str);
	return (1);
}

static char	*space_quote_env(char *value_elem, int hand_var)
{
	int		i;

	i = 0;
	while (value_elem[i])
		i++;
	i--;
	if (value_elem[i] == ' ')
	{
		while (i >= 0 && value_elem[i] == ' ')
			i--;
		value_elem[++i] = '\0';
	}
	value_elem = par_parse_quotes_and_vars(value_elem, hand_var);
	return (value_elem);
}

static int	between_pipe(t_par_elem **sub, int *fd_in, int *fd_out)
{
	if ((*sub) && (*sub)->type == OPER_HERE_DOC_N && *fd_in != NON_FD)
	{
		(*sub) = (*sub)->next;
		*fd_in = proc_here_doc(space_quote_env((*sub)->value, 0));
		if ((mistake_fd(*fd_in, "here_doc") == NON_HERE_DOC))
			return (NON_HERE_DOC);
	}
	else if ((*sub) && (*sub)->type == OPER_INP_N && (*sub)->type != DEFAULT_N
		&& (*sub)->type != OPER_DOLL_N && *fd_in != NON_FD)
	{
		*fd_in = proc_open_file(space_quote_env((*sub)->next->value, 1), READ);
		mistake_fd(*fd_in, (*sub)->next->value);
	}
	else if ((*sub) && (*sub)->type != DEFAULT_N
		&& (*sub)->type != OPER_DOLL_N && *fd_out != NON_FD)
	{
		if (sub && ((*sub)->type == OPER_OUT_N))
			*fd_out = proc_open_file(space_quote_env((*sub)->next->value, 1),
					WRITE);
		else if (sub && ((*sub)->type == OPER_OUT_APP_N))
			*fd_out = proc_open_file(space_quote_env((*sub)->next->value, 1),
					WRITE_APP);
		mistake_fd(*fd_out, (*sub)->next->value);
	}
	return (1);
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
		else if (sub && sub->type != DEFAULT_N && sub->type != OPER_DOLL_N)
			if (between_pipe(&sub, &fd_input, &fd_output) == NON_HERE_DOC)
				return (fd_arr);
		sub = sub->next;
	}
	return (fd_arr);
}
