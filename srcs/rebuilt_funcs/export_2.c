/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 19:05:08 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/12/19 15:44:37 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/rebuilt_funcs.h"

void	add_empty(char *new_name)
{
	t_env_elem	*elem;

	elem = env_get_by_name(g_data.envp, new_name);
	if (elem)
	{
		free(elem->value);
		elem->value = NULL;
		return ;
	}
	elem = (t_env_elem *)malloc(sizeof(t_env_elem));
	if (!elem)
		return ;
	elem->name = ft_strdup(new_name);
	elem->value = NULL;
	elem->prev = NULL;
	elem->next = NULL;
	env_push_back_elem(g_data.envp, elem);
}

void	add_value(char *new_name, char *new_val)
{
	char	*str;

	if (!new_val)
	{
		add_empty(new_name);
		free(new_name);
		return ;
	}
	if (env_set_by_name(g_data.envp, new_name, new_val))
		free(new_name);
	else
	{
		str = NULL;
		utils_append_string(&str, new_name);
		utils_append_string(&str, "=");
		utils_append_string(&str, new_val);
		env_push_back(g_data.envp, str);
		free(str);
		free(new_name);
		free(new_val);
	}
}
