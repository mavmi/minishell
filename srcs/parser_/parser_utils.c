/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 19:22:44 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/11/20 13:08:09 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser_.h"

// Create array of defined operators.
// May return NULL
char	**pars_get_operators(void)
{
	char	**arr;

	arr = (char **)malloc(sizeof(char *) * (OPERATORS + 1));
	if (!arr)
		return (NULL);
	arr[REDIR_OUT_N] = REDIR_OUT_S;
	arr[REDIR_INP_N] = REDIR_INP_S;
	arr[REDIR_OUT_APP_N] = REDIR_OUT_APP_S;
	arr[HERE_DOC_N] = HERE_DOR_S;
	arr[PIPE_N] = PIPE_S;
	arr[DOLL_N] = DOLL_S;
	arr[EQUAL_N] = EQUAL_S;
	arr[7] = NULL;
	return (arr);
}

// If cmd is operator, return it's position in opers array,
// -1 otherwise
int	pars_cmp_with_opers(char *cmd, char **opers)
{
	size_t	len;
	size_t	max_len;
	int		max_len_pos;
	int		pos;

	if (!cmd || !opers)
		return (-1);
	pos = 0;
	max_len = 0;
	max_len_pos = -1;
	while (pos < OPERATORS)
	{
		len = ft_strlen(opers[pos]);
		if (ft_strnstr(cmd, opers[pos], len) && max_len < len)
		{
			max_len = len;
			max_len_pos = pos;
		}
		pos++;
	}
	return (max_len_pos);
}

// Create operator's elem and push_back it into the list.
// Return 0 if everything is ok,
// 1 otherwise
int	pars_insert_elem(t_pars_list **list, char *str, int type)
{
	t_pars_list	*elem;

	if (!str)
		return (1);
	elem = pars_get_new_elem(type, str);
	if (!elem)
		return (1);
	if (!*list)
	{
		*list = elem;
		return (0);
	}
	pars_push_back(*list, elem);
	return (0);
}

int	pars_get_substr_len(char *cmd, char **opers)
{
	int	i;
	int	size;	

	if (!cmd || !opers)
		return (0);
	size = 0;
	while (cmd[size])
	{
		if (cmd[size] == ' ')
			return (size);
		if (cmd[size] == '\'' || cmd[size] == '\"')
			return (size);
		i = 0;
		while (i < OPERATORS)
		{
			if (cmd[size] == opers[i][0])
				return (size);
			i++;
		}
		size++;
	}
	return (size);
}

// Check if command contains forbidden symbols.
// Return 1 if it does,
// 0 otherwise
int	pars_is_forbidden(char *cmd)
{
	if (!cmd)
		return (1);
	while (*cmd)
	{
		if (*cmd == '\\' || *cmd == ';')
			return (1);
		cmd++;
	}
	return (0);
}
