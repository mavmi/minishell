/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 21:14:31 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/12/12 11:49:25 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/processes.h"

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
}
