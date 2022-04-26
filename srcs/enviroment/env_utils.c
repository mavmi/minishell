/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 13:22:34 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/11/28 13:24:57 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/enviroment.h"

// Print error from global variable and
// assign it to NULL
void	env_print_error(void)
{
	if (!g_data.error)
		return ;
	ft_putendl_fd(g_data.error, STDERR_FILENO);
	g_data.error = NULL;
}
