/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 17:43:00 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/12/19 15:34:36 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/enviroment.h"

// Remove element with specified name from the enviroment
void	env_remove_elem(t_enviroment *env, char *name)
{
	t_env_elem	*elem;
	t_env_elem	*prev;
	t_env_elem	*next;

	if (!env || !name)
		return ;
	elem = env_get_by_name(env, name);
	if (!elem)
		return ;
	prev = elem->prev;
	next = elem->next;
	if (prev)
		prev->next = next;
	if (next)
		next->prev = prev;
	env->size--;
	if (!elem->next)
		g_data.envp->end = elem->prev;
	if (!g_data.envp->end)
		g_data.envp->begin = NULL;
	free(elem->name);
	free(elem->value);
	free(elem);
}

// Destroy whole enviroment list
void	env_destroy(t_enviroment *env)
{
	t_env_elem	*elem;
	t_env_elem	*tmp;

	if (!env)
		return ;
	elem = env->begin;
	while (elem)
	{
		tmp = elem->next;
		free(elem->name);
		free(elem->value);
		free(elem);
		elem = tmp;
	}
	free(env);
}

// Create empty t_enviroment struct.
// May return NULL
t_enviroment	*env_create_empty(void)
{
	t_enviroment	*enviroment;

	enviroment = (t_enviroment *)malloc(sizeof(t_enviroment));
	if (!enviroment)
		return (NULL);
	enviroment->begin = NULL;
	enviroment->end = NULL;
	enviroment->size = 0;
	return (enviroment);
}

// Create new t_enviroment struct and
// fill it with strings from [envp].
// May return NULL
t_enviroment	*env_create(char **envp)
{
	t_enviroment	*env;

	env = env_create_empty();
	if (!env)
		return (NULL);
	while (*envp)
	{
		env_push_back(env, *envp);
		envp++;
	}
	return (env);
}
