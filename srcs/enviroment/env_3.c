/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 17:43:12 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/11/10 14:02:12 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/enviroment.h"

// Get env element at position [pos].
// May return NULL
t_env_elem	*env_get_by_position(t_enviroment *env, size_t pos)
{
	size_t		i;
	t_env_elem	*ptr;

	if (!env || pos >= env->size)
		return (NULL);
	i = 0;
	ptr = env->begin;
	while (i != pos)
	{
		ptr = ptr->next;
		i++;
	}
	return (ptr);
}

// Get env elemnt with name [name].
// May return NULL
t_env_elem	*env_get_by_name(t_enviroment *env, char *name)
{
	t_env_elem	*elem;

	if (!env || !name || !env->size)
		return (NULL);
	elem = env->begin;
	while (elem)
	{
		if (utils_cmp_strings(elem->name, name))
			return (elem);
		elem = elem->next;
	}
	return (NULL);
}

// Set new value string to evniroment's element at position [pos].
// Return 1 if everything is ok, 0 otherwise
int	env_set_by_position(t_enviroment *env, size_t pos, char *new_val)
{
	t_env_elem	*elem;

	if (!env || pos >= env->size || !new_val)
		return (0);
	elem = env_get_by_position(env, pos);
	if (!elem)
		return (0);
	free(elem->value);
	elem->value = new_val;
	return (1);
}

// Set new value string to evniroment's element with name [name].
// Return 1 if everything is ok, 0 otherwise
int	env_set_by_name(t_enviroment *env, char *name, char *new_val)
{
	t_env_elem	*elem;

	if (!env || !name || !new_val)
		return (0);
	elem = env_get_by_name(env, name);
	if (!elem)
		return (0);
	free(elem->value);
	elem->value = new_val;
	return (1);
}
