/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 18:28:49 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/12/11 15:18:56 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/rebuilt_funcs.h"

void	rebuilt_unset(int argc, char **argv)
{
	int	i;	

	if (argc == 1 || !argv)
		return ;
	i = 1;
	while (i < argc)
		env_remove_elem(g_data.envp, argv[i++]);
}
