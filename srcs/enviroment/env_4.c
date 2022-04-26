/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 19:02:35 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/12/18 19:03:06 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/enviroment.h"

// Create new env element
// and push it to the end of enviroment struct.
// Return 0 if everything is ok,
// 1 otherwise
int	env_push_back(t_enviroment *env, char *str)
{
	t_env_elem	*new_elem;

	if (!str)
		return (1);
	new_elem = env_get_new_elem(str);
	if (!new_elem)
		return (1);
	if (env->size)
	{
		env->end->next = new_elem;
		new_elem->prev = env->end;
		env->end = new_elem;
	}
	else
	{
		env->begin = new_elem;
		env->end = new_elem;
	}
	env->size++;
	return (0);
}

void	env_push_back_elem(t_enviroment *env, t_env_elem *new_elem)
{
	if (!new_elem)
		return ;
	if (env->size)
	{
		env->end->next = new_elem;
		new_elem->prev = env->end;
		env->end = new_elem;
	}
	else
	{
		env->begin = new_elem;
		env->end = new_elem;
	}
	env->size++;
}
