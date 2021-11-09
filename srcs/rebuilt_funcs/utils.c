/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 17:47:57 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/11/09 17:53:25 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/rebuilt_funcs.h"

int	is_rebuild(char *func)
{
	if (!func)
		return (0);
	if (cmp_strings(ECHO, func))
		return (1);
	if (cmp_strings(CD, func))
		return (1);
	if (cmp_strings(PWD, func))
		return (1);
	if (cmp_strings(EXPORT, func))
		return (1);
	if (cmp_strings(UNSET, func))
		return (1);
	if (cmp_strings(ENV, func))
		return (1);
	if (cmp_strings(EXIT, func))
		return (1);
	return (0);
}
