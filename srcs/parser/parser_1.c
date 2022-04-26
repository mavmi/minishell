/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalena <msalena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 19:30:03 by msalena           #+#    #+#             */
/*   Updated: 2021/10/27 23:11:16 by msalena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

/* Frees operations arr and/or list */
t_par_list	*par_free_out(char **oper_arr, t_par_list *list, int fl)
{
	free(oper_arr);
	if (fl == 1)
	{
		par_destroy_all(list);
		return (NULL);
	}
	return (list);
}

char	*par_check_malloc(char *str)
{
	char	*return_str;

	if (!str)
		return (NULL);
	return_str = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!return_str)
	{
		free (str);
		return (NULL);
	}
	return (return_str);
}

/* compares input elem of cmd with define operators
--> return number of rediretive if match
	or -1 (DEFAULT) if cmd[i] doesn't match */
int	par_compar_cNo(char *cmd, t_par_count *coun, char **oper)
{
	int	n_str;
	int	t;
	int	n_el;

	t = 0;
	n_str = 0;
	n_el = 0;
	coun->size = 0;
	coun->num = DEFAULT_N;
	if (!cmd || !coun || !oper)
		return (0);
	while (oper[n_str])
	{
		while (oper[n_str][n_el] && cmd[t] && cmd[t++] == oper[n_str][n_el])
			n_el++;
		if (!oper[n_str][n_el] && n_el > coun->size)
		{
			coun->size = n_el;
			coun->num = n_str;
		}
		n_el = 0;
		t = 0;
		n_str++;
	}
	return (coun->num);
}

/* Finds quotion marks */
static char	*between_quotes(char *str, char *return_str,
							int *str_c, int *retstr_c)
{
	char	quote;

	quote = 0;
	quote = str[*str_c];
	return_str[(*retstr_c)++] = str[(*str_c)++];
	while (str[*str_c] != quote)
	{
		return_str[(*retstr_c)++] = str[(*str_c)++];
	}
	return_str[(*retstr_c)++] = str[(*str_c)++];
	return (return_str);
}

/* Handls quotes in substr
--> return changed substr
	or NULL if some mistake */
char	*par_handling_quotes(char *str)
{
	int		str_c;
	int		retstr_c;
	char	*return_str;

	str_c = 0;
	retstr_c = 0;
	if (!str)
		return (NULL);
	return_str = par_check_malloc(str);
	if (!return_str)
		return (NULL);
	while (str[str_c])
	{
		while (str[str_c] && str[str_c] != '\'' && str[str_c] != '\"')
			return_str[retstr_c++] = str[str_c++];
		if (str[str_c] == '\'' || str[str_c] == '\"')
			between_quotes(str, return_str, &str_c, &retstr_c);
	}
	return_str[retstr_c] = '\0';
	free (str);
	return (return_str);
}
