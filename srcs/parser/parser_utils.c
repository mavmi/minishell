/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 17:42:04 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/12/19 17:49:19 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

int	par_is_valid_symbol(char c)
{
	if (c == '_' || ft_isdigit(c) || ft_isalpha(c))
		return (1);
	return (0);
}

char	*par_strchr(char *str)
{
	if (!str)
		return (NULL);
	while (*str)
	{
		if (!par_is_valid_symbol(*str))
			return (str);
		str++;
	}
	return (NULL);
}
