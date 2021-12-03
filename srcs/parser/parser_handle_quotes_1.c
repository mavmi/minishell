/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_handle_quotes_1.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 15:55:35 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/12/03 17:08:55 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

static size_t	par_get_arr_len(char **array)
{
	size_t	len;

	if (!array)
		return (0);
	len = 0;
	while (*array)
	{
		len++;
		array++;
	}
	return (len);
}

char	**par_handle_quotes(char **commands)
{
	int		iter;
	char	**output;

	if (!commands)
		return (NULL);
	output = (char **)malloc(sizeof(char *) * (par_get_arr_len(commands) + 1));
	if (!output)
		return (NULL);
	iter = 0;
	while (commands[iter])
	{
		output[iter] = par_handle_str(commands[iter]);
		if (!output[iter])
		{
			while (iter >= 0)
				free(output[iter--]);
			free(output);
			return (NULL);
		}
		iter++;
	}
	output[iter] = NULL;
	return (output);
}
