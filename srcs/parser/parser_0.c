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

/* Creates substr from start to finded end
--> return substr
	or NULL if some mistake*/
static char	*get_return_substr(char *cmd, int start, t_par_count *count)
{
	char	*return_str;
	int		j;

	j = 0;
	return_str = (char *)malloc(sizeof(char) * (count->i_elem - start + 2));
	if (!return_str)
		return (NULL);
	while (cmd[start] && start < count->i_elem)
		return_str[j++] = cmd[start++];
	return_str[j] = '\0';
	return_str = par_handling_quotes(return_str);
	if (!return_str)
		return (NULL);
	return (return_str);
}

/* Iterates to the end of quotes area
--> reutrn 1 if quotes are closed
	or 0 if there aren't even quotes num in cmd */
static int	end_of_quotes_area(char *cmd, t_par_count *count, int start)
{
	char	quote;

	quote = cmd[count->i_elem];
	count->i_elem++;
	while (cmd[count->i_elem] && cmd[count->i_elem] != quote)
	{
		count->i_elem++;
	}
	if (!cmd[count->i_elem])
	{
		count->i_elem = start;
		ft_putendl_fd("minishell: error: invalid quotes", STDERR_FILENO);
		return (0);
	}
	else
		return (1);
}

/* Finds end of substr
--> reutrn NULL if mistake */
static char	*end_of_argum_str(char *cmd, t_par_count *count,
											char **oper_arr, int start)
{
	int	safe_num_count;
	int	op_fl;

	safe_num_count = count->num;
	op_fl = par_compar_cNo(cmd + count->i_elem, count, oper_arr);
	if (op_fl == OPER_DOLL_N)
		op_fl = par_compar_cNo(cmd + ++count->i_elem, count, oper_arr);
	while (cmd[count->i_elem] && (op_fl == DEFAULT_N || op_fl == OPER_DOLL_N))
	{
		if (cmd[count->i_elem] == ' ')
		{
			while (cmd[count->i_elem + 1] == ' ')
				count->i_elem++;
			count->i_elem++;
			break ;
		}
		if (cmd[count->i_elem] == '\'' || cmd[count->i_elem] == '\"')
			if (end_of_quotes_area(cmd, count, start) == 0)
				return (NULL);
		count->i_elem++;
		op_fl = par_compar_cNo(cmd + count->i_elem, count, oper_arr);
	}
	count->num = safe_num_count;
	return (cmd);
}

/* Gets substr
--> reutrn substr or
	NULL if some mistake */
static char	*get_elems(char *cmd, char **oper_arr, t_par_count *coun)
{
	int	start;
	int	compar_res;

	start = coun->i_elem;
	compar_res = -2;
	while (cmd[coun->i_elem] == ' ')
		coun->i_elem++;
	while (1)
	{
		compar_res = par_compar_cNo(cmd + coun->i_elem, coun, oper_arr);
		if (cmd[coun->i_elem] && compar_res != DEFAULT_N
			&& compar_res != OPER_DOLL_N)
		{
			coun->i_elem += ft_strlen(oper_arr[compar_res]);
			return (oper_arr[compar_res]);
		}
		start = coun->i_elem;
		if (end_of_argum_str(cmd, coun, oper_arr, start) == NULL)
			return (NULL);
		if (cmd[start] && start != coun->i_elem)
			return (get_return_substr(cmd, start, coun));
		if (!cmd[coun->i_elem])
			return (NULL);
	}
	return (NULL);
}

/* Separates cmd on substrs
--> reutrn list of substrs
	or NULL if some mistake */
t_par_list	*par_split(char *cmd)
{
	t_par_list	*list;
	char		*substr;
	char		**oper_arr;
	t_par_count	coun;

	if (!cmd)
		return (NULL);
	coun = par_count_initial();
	oper_arr = par_get_redirect();
	list = par_initial_empty_list();
	if (!oper_arr || !list)
		return (par_free_out(oper_arr, list, 1));
	substr = get_elems(cmd, oper_arr, &coun);
	if (!substr)
		return (par_free_out(oper_arr, list, 1));
	while (substr)
	{
		par_push_back(par_get_new_elem(coun.num, substr), list);
		if (coun.num == DEFAULT_N || coun.num == OPER_DOLL_N)
			free (substr);
		substr = get_elems(cmd, oper_arr, &coun);
		if (!substr && (int)ft_strlen(cmd) != coun.i_elem)
			return (par_free_out(oper_arr, list, 1));
	}
	return (par_free_out(oper_arr, list, 0));
}
