/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_handle_quotes_1.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 15:55:35 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/12/18 14:06:15 by pmaryjo          ###   ########.fr       */
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

char	**par_handle_quotesNenv(char **commands)
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
		output[iter] = par_parse_quotes_and_vars(commands[iter], 1);
		if (!output[iter])
		{
			while (iter >= 0)
				free(output[iter--]);
			free(output);
			utils_destroy_strings_array(commands);
			return (NULL);
		}
		iter++;
	}
	output[iter] = NULL;
	utils_destroy_strings_array(commands);
	return (output);
}
