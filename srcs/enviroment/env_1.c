/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 17:42:54 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/12/19 18:11:29 by pmaryjo          ###   ########.fr       */
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
		if (elem->value || (!elem->value && fl_empty))
			size++;
		elem = elem->next;
	}
	return (size);
}

static int	ft_kostil(char **arr)
{
	utils_destroy_strings_array(arr);
	return (1);
}

static int	handler(int fl_emp, t_env_elem *elem, int *i, char **result)
{
	if (fl_emp)
	{
		if (!elem->value)
			result[*i] = utils_create_lone_string(elem->name, "");
		else
			result[*i] = utils_create_lone_string(elem->name, elem->value);
		if (!result[(*i)++])
			return (ft_kostil(result));
	}
	else
	{
		if (elem->value)
		{
			result[*i] = utils_create_lone_string(elem->name, elem->value);
			if (!result[(*i)++])
				return (ft_kostil(result));
		}
	}
	return (0);
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
		if (handler(fl_emp, elem, &i, result))
			return (NULL);
		elem = elem->next;
	}
	result[i] = NULL;
	return (result);
}
