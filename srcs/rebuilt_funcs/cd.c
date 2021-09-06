/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 17:11:47 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/09/04 16:24:17 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/rebuilt_funcs.h"

// Change working directory to [argv[1]].
// At first it tries to use [argv[1]] as absolute path
void	cd(int argc, char **argv)
{
	if (argc == 1)
		return ;
	if (chdir(argv[1]))
	{
		perror(strerror(errno));
		return ;
	}
	// изменить env pwd
}
