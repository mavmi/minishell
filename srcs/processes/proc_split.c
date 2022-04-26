/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 21:14:31 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/12/12 13:31:32 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/processes.h"
/*
static char	*quotes(char *str, int *begin, int fl_size)
{
	int		end;
	char	*tmp;

	tmp = ft_strchr(str + *begin + 1, str[*begin]);
	if (!tmp)
		return (NULL);
	end = tmp - str;
	tmp = NULL;
	if (!fl_size)
		tmp = ft_substr(str, *begin, end - *begin + 1);
	*begin = end + 1;
	return (tmp);
}

static char	*non_quotes(char *str, int *begin, int fl_size)
{
	int		end;
	char	*tmp;

	tmp = ft_strchr(str + *begin + 1, ' ');
	if (!tmp)
		tmp = ft_strchr(str + *begin + 1, '\'');
	if (!tmp)
		tmp = ft_strchr(str + *begin + 1, '\"');
	if (tmp)
	{
		end = tmp - str;
		tmp = NULL;
		if (!fl_size)
			tmp = ft_substr(str, *begin, end - *begin);
		*begin = end;
	}
	else
	{
		tmp = NULL;
		if (!fl_size)
			tmp = ft_substr(str, *begin, ft_strlen(str + *begin));
		*begin += ft_strlen(str + *begin);
	}
	return (tmp);
}

static int	add_to_array(char ***array, char *str, int *i, int fl_size)
{
	if (!fl_size)
	{
		if (!str)
		{
			utils_destroy_strings_array(*array);
			return (1);
		}
		(*array)[(*i)] = str;
		(*i)++;
	}
	return (0);
}

static int	get_some_memore(char ***array, size_t *size, int fl_size)
{
	if (!fl_size)
	{
		*array = (char **)malloc(sizeof(char *) * (*size + 1));
		if (!*array)
			return (1);
	}
	return (0);
}

void	proc_split(char *str, char ***array, size_t *size, int fl_size)
{
	int		i;
	int		pos;

	if (!str || get_some_memore(array, size, fl_size))
		return ;
	i = 0;
	*size = 0;
	pos = 0;
	while (str[pos])
	{
		if (str[pos] == ' ')
		{
			pos++;
			continue ;
		}
		if ((str[pos] == '\'' || str[pos] == '\"')
			&& add_to_array(array, quotes(str, &pos, fl_size), &i, fl_size))
			return ;
		if ((str[pos] && str[pos] != '\'' && str[pos] != '\"' && str[pos] != ' ')
			&& add_to_array(array, non_quotes(str, &pos, fl_size), &i, fl_size))
			return ;
		(*size)++;
	}
	if (!fl_size)
		(*array)[i] = NULL;
}*/

static int	par_push_bach(char ***arr, char *str)
{
	int		i;
	char	**tmp;
	size_t	size;

	if (!arr || !str)
		return (1);
	size = 0;
	while (*arr && (*arr)[size])
		size++;
	tmp = (char **)malloc(sizeof(char *) * (size + 2));
	if (!tmp)
		return (1);
	i = 0;
	while (*arr && (*arr)[i])
	{
		tmp[i] = (*arr)[i];
		i++;
	}
	tmp[i++] = str;
	tmp[i++] = NULL;
	free(*arr);
	*arr = tmp;
	return (0);
}

static int	end_of_quotes_area(char *cmd, int *i)
{
	char	quote;

	quote = cmd[*i];
	(*i)++;
	while (cmd[*i] && cmd[*i] != quote)
	{
		(*i)++;
	}
	return (1);
}

static void	delete_spases(char *new_elem)
{
	int	i;

	i = 0;
	while (new_elem[i + 1])
		i++;
	while (i >= 0 && new_elem[i] == ' ')
		i--;
	new_elem[++i] = '\0';
}

static char	*end_of_argum_str(char *cmd, int *i)
{
	int	start;
	int	end;

	start = *i;
	end = start;
	while (cmd[*i])
	{
		if (cmd[*i] == ' ')
		{
			while (cmd[*i + 1] == ' ')
				(*i)++;
			(*i)++;
			end = (*i);
			break ;
		}
		if (cmd[*i] == '\'' || cmd[*i] == '\"')
			if (end_of_quotes_area(cmd, i) == 0)
				return (NULL);
		(*i)++;
	}
	end = *i;
	return (ft_substr(cmd, start, end - start));
}

char	**proc_split(char *cmd)
{
	char	**return_arr;
	char	*new_elem;
	int		arr_i;

	if (!cmd)
		return (NULL);
	arr_i = 0;
	return_arr = NULL;
	while (cmd[arr_i])
	{
		new_elem = end_of_argum_str(cmd, &arr_i);
		delete_spases(new_elem);
		if (par_push_bach(&return_arr, new_elem))
		{
			utils_destroy_strings_array(return_arr);
			return (NULL);
		}
	}	
	return (return_arr);
}
