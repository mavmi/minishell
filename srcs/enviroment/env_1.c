/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 17:42:54 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/12/11 17:00:18 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/enviroment.h"

// Create new t_env_elem struct.
// May return NULL
t_env_elem	*env_get_new_elem(char *str)
{
	int			eq_pos;
	char		*eq_ptr;
	t_env_elem	*new_elem;

	if (!str)
		return (NULL);
	eq_ptr = ft_strchr(str, '=');
	if (!eq_ptr)
		return (NULL);
	new_elem = (t_env_elem *)malloc(sizeof(t_env_elem));
	if (!new_elem)
		return (NULL);
	eq_pos = eq_ptr - str;
	new_elem->name = ft_substr(str, 0, eq_pos);
	new_elem->value = ft_substr(str, eq_pos + 1, ft_strlen(str) - eq_pos);
	if (!new_elem->name || !new_elem->value)
	{
		free(new_elem->name);
		free(new_elem->value);
		free(new_elem);
		return (NULL);
	}
	new_elem->next = NULL;
	new_elem->prev = NULL;
	return (new_elem);
}

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

static size_t	get_env_size(t_enviroment *env, int fl_empty)
{
	size_t		size;
	t_env_elem	*elem;

	if (!env)
		return (0);
	size = 0;
	elem = env->begin;
	while (elem)
	{
		if (ft_strlen(elem->value) || fl_empty)
			size++;
		elem = elem->next;
	}
	return (size);
}

static char	**ft_kostil(char **arr)
{
	utils_destroy_strings_array(arr);
	return (NULL);
}

// Get array of strings from enviroment struct.
// May return NULL
char	**env_get_content(t_enviroment *env, int fl_emp)
{
	int			i;
	char		**result;
	t_env_elem	*elem;

	if (!env)
		return (NULL);
	result = (char **)malloc(sizeof(char *) * (get_env_size(env, fl_emp) + 1));
	if (!result)
		return (NULL);
	i = 0;
	elem = env->begin;
	while (elem)
	{
		if (ft_strlen(elem->value) || fl_emp)
		{
			result[i] = utils_create_lone_string(elem->name, elem->value);
			if (!result[i++])
				return (ft_kostil(result));
		}
		elem = elem->next;
	}
	result[i] = NULL;
	return (result);
}
