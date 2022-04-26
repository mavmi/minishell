/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 18:56:24 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/12/11 16:46:01 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/utils.h"

// [name] + [value] ==> "[name]=[value]"
char	*utils_create_lone_string(char *name, char *value)
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

// Compare strings.
// Return 1 if strings are equal,
// 0 otherwise
int	utils_cmp_strings(char *s1, char *s2)
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

char	*utils_sum_strings(char *s1, char *s2)
{
	size_t	i;
	char	*result;

	if (!s1 || !s2)
		return (NULL);
	result = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!result)
		return (NULL);
	i = 0;
	while (*s1)
		result[i++] = *s1++;
	while (*s2)
		result[i++] = *s2++;
	result[i] = 0;
	return (result);
}

void	utils_append_string(char **str, char *value)
{
	char	*tmp;

	if (!str || !value)
		return ;
	if (!*str)
	{
		*str = ft_strdup(value);
		return ;
	}
	tmp = utils_sum_strings(*str, value);
	free(*str);
	*str = tmp;
}

void	utils_destroy_strings_array(char **arr)
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
