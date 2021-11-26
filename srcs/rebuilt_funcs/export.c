/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 15:33:33 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/11/26 16:45:05 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/rebuilt_funcs.h"

void	rebuilt_export(int argc, char **argv)
{
	char	*str;
	char	*new_name;
	char	*new_val;
	char	**array;

	if (argc != 3 || !argv[1] || !argv[2])
		return ;
	str = NULL;
	new_name = ft_strdup(argv[1]);
	new_val = ft_strdup(argv[2]);
	if (env_set_by_name(g_data.envp, new_name, new_val))
		free(new_name);
	else
	{
		utils_append_string(&str, new_name);
		utils_append_string(&str, "=");
		utils_append_string(&str, new_val);
		env_push_back(g_data.envp, str);
		free(str);
		free(new_name);
		free(new_val);
	}
}
