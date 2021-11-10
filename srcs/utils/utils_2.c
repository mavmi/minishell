/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 15:55:28 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/11/10 14:38:21 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/utils.h"

static int	free_and_exit(char *str, int ret_val)
{
	free(str);
	return (ret_val);
}

// Check if variable's name in [str] contains only letters,
// digits and underscores.
// Return if [str] is valid, 0 otherwise
int	utils_is_string_valid(char *str)
{
	char	*name;
	char	*eq;
	int		i;

	eq = ft_strchr(str, '=');
	if (!eq)
		return (0);
	name = ft_substr(str, 0, eq - str);
	if (!name || !ft_strlen(name))
		return (free_and_exit(name, 0));
	i = 0;
	if (!ft_isalpha(name[i]) && name[i] != '_')
		return (free_and_exit(name, 0));
	while (name[++i])
	{
		if (!ft_isalpha(name[i]) && !ft_isdigit(name[i]) && name[i] != '_')
			return (free_and_exit(name, 0));
	}
	return (free_and_exit(name, 1));
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
