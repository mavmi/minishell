/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_sort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 18:06:30 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/12/10 19:04:39 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/enviroment.h"

static int	ft_strcmp(char *s1, char *s2)
{
	int				result;
	unsigned int	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		result = (unsigned char)s1[i] - (unsigned char)s2[i];
		if (result != 0)
		{
			return (result);
		}
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

static void	sort_list(t_enviroment *copy_list)
{
	t_env_elem	*elem_1;
	t_env_elem	*elem_2;
	int			swap_fl;
	
	elem_1 = copy_list->begin;
	elem_2 = elem_1;
	swap_fl = 0;
	while (elem_1)
	{
		elem_2 = elem_1;
		while (elem_2)
		{
			if (ft_strcmp(elem_1->name, elem_2->name) > 0)
			{
				//swap	
			}			
			elem_2 = elem_2->next;			
		}
		elem_1 = elem_1->next;
	}	
}

t_enviroment	*env_sort(void)
{
	char			**env;
	t_enviroment	*copy_list;

	env = env_get_content(g_data.envp);
	if (!env)
		return (NULL);
	copy_list = env_create(env);
	if (!copy_list)
	{
		utils_destroy_strings_array(env);
		return (NULL);
	}
	sort_list(copy_list);
	return (copy_list);
}