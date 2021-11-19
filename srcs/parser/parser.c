/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalena <msalena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 19:30:00 by msalena           #+#    #+#             */
/*   Updated: 2021/10/26 19:30:01 by msalena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

static char	*get_return_substr(char *cmd, int start, t_par_count *count)
{
	char	*return_str;
	int		j;

	return_str = NULL;
	j = 0;
	return_str = (char *)malloc(sizeof(char) * (count->i_elem - start + 2));
	if (!return_str)
		return (NULL);
	while (cmd[start] && start < count->i_elem)
		return_str[j++] = cmd[start++];
	return_str[j] = '\0';
	return_str = par_handling_quotes(return_str);
	if (!return_str)
	{
		free (return_str);
		return (NULL);
	}
	return (return_str);
}

static int	find_end_of_quotes_area(char *cmd, t_par_count *count, char quote)
{
	count->i_elem++;
	while (cmd[count->i_elem] && cmd[count->i_elem] != quote)
	{
		count->i_elem++;
	}
	if (!cmd[count->i_elem])
		return (0);
	else
		return (1);
}

static char	*find_end_of_argum_str(char *cmd, t_par_count *count,
											char **arr_redir)
{
	int	safe_num_count;
	int	OPER_fl;
	int	safe_i_elem;

	safe_num_count = count->num;
	safe_i_elem = count->i_elem;
	OPER_fl = par_compar_cNo(cmd + count->i_elem, count, arr_redir);
	while (cmd[count->i_elem] && cmd[count->i_elem] != ' '
		&& (OPER_fl == DEFAULT_N || OPER_fl == OPER_DOLL_N))
	{
		if (cmd[count->i_elem] == '\'' || cmd[count->i_elem] == '\"')
		{
			if (find_end_of_quotes_area(cmd, count, cmd[count->i_elem]) == 0)
			{
				count->i_elem = safe_i_elem;
				return (NULL);
			}
		}
		count->i_elem++;
		OPER_fl = par_compar_cNo(cmd + count->i_elem, count, arr_redir);
	}
	count->size = 0;
	count->num = safe_num_count;
	return (cmd);
}

static char	*get_elems(char *cmd, char **arr_redir, t_par_count *coun)
{
	int	start;
	int	compar_res;

	start = coun->i_elem;
	compar_res = -2;
	while (cmd[coun->i_elem] == ' ')
		coun->i_elem++;
	while (1)
	{
		compar_res = par_compar_cNo(cmd + coun->i_elem, coun, arr_redir);
		if (cmd[coun->i_elem] && compar_res != DEFAULT_N
			&& compar_res != OPER_DOLL_N)
		{
			coun->i_elem += ft_strlen(arr_redir[compar_res]);
			return (arr_redir[compar_res]);
		}
		start = coun->i_elem;
		if (find_end_of_argum_str(cmd, coun, arr_redir) == NULL)
			return (NULL);
		if (cmd[start] && start != coun->i_elem)
			return (get_return_substr(cmd, start, coun));
		if (!cmd[coun->i_elem])
			return (NULL);
	}
	return (NULL);
}

t_par_list	*par_split(char *cmd)
{
	t_par_list	*list;
	char		*substr;
	char		**oper_arr;
	t_par_count	coun;

	if (!cmd)
		return (NULL);
	coun = count_initial();
	oper_arr = par_get_redirect();
	list = par_initial_empty_list();
	if (!oper_arr || !list)
		return (NULL);
	substr = get_elems(cmd, oper_arr, &coun);
	if (!substr)
		return (par_free_out(oper_arr, list));
	while (substr)
	{
		par_push_back(par_get_new_elem(coun.num, substr), list);
		substr = get_elems(cmd, oper_arr, &coun);
		if (!substr && (int)ft_strlen(cmd) != coun.i_elem)
			return (par_free_out(oper_arr, list));
	}
	return (list);
}
