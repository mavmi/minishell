/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 17:22:13 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/11/27 14:39:22 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser_.h"

// Try to parse string.
// Return 0 if evetything is done,
// -1 if an error occured
static int	pars_handle_strings(t_pars_list **list, char **cmd, char **opers)
{
	int		len;
	char	*tmp;
	char	*substr;

	if (!cmd || !opers)
		return (1);
	len = pars_get_substr_len(*cmd, opers);
	if (len)
	{
		tmp = ft_substr(*cmd, 0, len);
		substr = pars_get_whole_string(tmp);
		free(tmp);
		if (!substr || pars_insert_elem(list, substr, DEFAULT))
		{
			free(opers);
			free(substr);
			pars_destroy_list(*list);
			return (1);
		}
		free(substr);
		*cmd += len;
	}
	return (0);
}

// Try to parse operator element.
// Return 0 if evetything is done,
// 1 if it is not an operator and
// -1 if an error occured
static int	pars_handle_opers(t_pars_list **list, char **cmd, char **opers)
{
	int	number;

	if (!cmd || !opers)
		return (-1);
	number = pars_cmp_with_opers(*cmd, opers);
	if (number != -1)
	{
		if (pars_insert_elem(list, opers[number], number))
		{
			free(opers);
			pars_destroy_list(*list);
			return (-1);
		}
		*cmd += ft_strlen(opers[number]);
		return (0);
	}
	return (1);
}

// Return 0 if everything is ok,
// 1 otherwise
static int	pars_split_handler(t_pars_list **list, char *cmd, char **opers)
{
	int	i;

	while (*cmd)
	{
		if (*cmd == ' ')
		{
			cmd += 1;
			continue ;
		}
		i = pars_handle_opers(list, &cmd, opers);
		if (i == -1)
			return (1);
		if (i == 0)
			continue ;
		if (pars_handle_strings(list, &cmd, opers))
			return (1);
	}
	return (0);
}

t_pars_list	*pars_split(char *cmd)
{
	char		**opers;
	t_pars_list	*list;

	if (!cmd || pars_is_forbidden(cmd))
		return (NULL);
	opers = pars_get_operators();
	if (!opers)
		return (NULL);
	list = NULL;
	if (pars_split_handler(&list, cmd, opers))
		return (NULL);
	free(opers);
	return (list);
}
