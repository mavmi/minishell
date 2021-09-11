/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 18:56:24 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/09/11 16:03:52 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/utils.h"

// [name] + [value] ==> "[name]=[value]"
char	*create_lone_string(char *name, char *value)
{
	int		i;
	char	*str;

	if (!name || !value)
		return (NULL);
	str = (char *)malloc(ft_strlen(name) + ft_strlen(value) + 2);
	if (!str)
		return (NULL);
	i = 0;
	while (*name)
		str[i++] = *name++;
	str[i++] = '=';
	while (*value)
		str[i++] = *value++;
	str[i] = 0;
	return (str);
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
