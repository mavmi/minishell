/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 19:20:45 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/12/18 18:56:32 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/rebuilt_funcs.h"

void	rebuilt_env(int fd_out)
{
	char	**envp;
	char	**ptr;

	envp = env_get_content(g_data.envp, 0);
	ptr = envp;
	while (*ptr)
	{
		ft_putendl_fd(*ptr, fd_out);
		ptr++;
	}
	utils_destroy_strings_array(envp);
	g_data.exit_status = 0;
}
