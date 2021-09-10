/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 16:47:13 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/09/10 20:19:13 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/rebuilt_funcs.h"

void	pwd(void)
{
	char		*path;
	t_env_elem	*pwd_elem;
	
	pwd_elem = env_get_by_name(g_data->envp, "PWD");
	if (pwd_elem)
		printf("%s\n", pwd_elem->value);
	else
	{
		path = getcwd(NULL, 0);
		printf("%s\n", path);
		free(path);
	}
}
