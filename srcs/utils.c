/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 18:56:24 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/09/10 17:59:00 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/utils.h"

// Check if variable's name in [str] contains only letters,
// digits and underscores.
// Return if [str] is valid, 0 otherwise
int	is_string_valid(char *str)
{
	char	*name;
	char	*eq;
	int		i;

	eq = ft_strchr(str, '=');
	if (!eq)
		return (0);
	name = ft_substr(str, 0, eq - str);
	if (!name || !ft_strlen(name))
		return (0);
	i = 0;
	if (!ft_isalpha(name[i]) && name[i] != '_')
		return (0);
	while (name[++i])
	{
		if (!ft_isalpha(name[i]) && !ft_isdigit(name[i]) && name[i] != '_')
		{
			free(name);
			return (0);
		}
	}
	free(name);
	return (1);
}

// Compare strings.
// Return 1 if strings are equal,
// 0 otherwise
int	cmp_strings(char *s1, char *s2)
{
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 || !s2)
	{
		return (0);
	}
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	if (s1_len == s2_len && !ft_strncmp(s1, s2, s1_len))
	{
		return (1);
	}
	return (0);
}

void	destroy_strings_array(char **arr)
{
	char	**ptr;

	if (!arr)
		return ;
	ptr = arr;
	while (*ptr)
	{
		free(*ptr);
		ptr++;
	}
	free(arr);
}

// Get string of value assignment
// and convert it into array of strings:
// array[0] = name,
// array[1] = value.
// May return NULL if [str] is NULL or 
// if value name is invalid
char	**parse_varialbe(char *str)
{
	size_t	len;
	size_t	eq_pos;
	char	*eq;
	char	**array;

	len = ft_strlen(str);
	if (!str || !len || !is_string_valid(str))
		return (NULL);
	eq = ft_strchr(str, '=');
	if (!eq)
		return (NULL);
	array = (char **)malloc(sizeof(char *) * 3);
	if (!array)
		return (NULL);
	eq_pos = eq - str;
	array[0] = ft_substr(str, 0, eq_pos);
	array[1] = ft_substr(str, eq_pos + 1, len - eq_pos);
	array[2] = NULL;
	if (!array[0] || !array[1] || !ft_strlen(array[0]) || !ft_strlen(array[1]))
	{
		destroy_strings_array(array);
		return (NULL);
	}
	return (array);
}
