/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 15:33:33 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/11/10 14:41:47 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/rebuilt_funcs.h"

void	rebuilt_export(int argc, char **argv)
{
	char	*new_name;
	char	*new_val;
	char	**array;

	if (argc != 2 || !argv[1])
		return ;
	array = utils_parse_varialbe(argv[1]);
	if (!array)
		return ;
	new_name = ft_strdup(array[0]);
	new_val = ft_strdup(array[1]);
	if (env_set_by_name(g_data.envp, new_name, new_val))
		free(new_name);
	else
	{
		env_push_back(g_data.envp, argv[1]);
		free(new_name);
		free(new_val);
	}
	free(array[0]);
	free(array[1]);
	free(array);
}
