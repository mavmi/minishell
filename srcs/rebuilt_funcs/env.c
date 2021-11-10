/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 19:20:45 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/11/10 14:42:10 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/rebuilt_funcs.h"

void	rebuilt_env(void)
{
	char	**envp;
	char	**ptr;

	envp = env_get_content(g_data.envp);
	ptr = envp;
	while (*ptr)
	{
		printf("%s\n", *ptr);
		ptr++;
	}
	utils_destroy_strings_array(envp);
}
