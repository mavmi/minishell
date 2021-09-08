/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 18:56:24 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/09/08 16:14:56 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/utils.h"

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
