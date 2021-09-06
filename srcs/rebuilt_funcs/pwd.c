/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 16:47:13 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/09/03 17:24:53 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/rebuilt_funcs.h"

void	pwd(void)
{
	char	*cur_dir;

	cur_dir = getcwd(NULL, 0);
	if (cur_dir)
		printf("%s\n", cur_dir);
	else
		perror(strerror(errno));
}
