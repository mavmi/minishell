/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 18:28:49 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/11/10 14:41:29 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/rebuilt_funcs.h"

void	rebuilt_unset(int argc, char **argv)
{
	if (argc != 2 || !argv[1])
		return ;
	env_remove_elem(g_data.envp, argv[1]);
}
