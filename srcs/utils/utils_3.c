/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 14:00:16 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/11/21 14:01:04 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/utils.h"

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
