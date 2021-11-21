/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 15:54:30 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/11/21 16:42:11 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/rebuilt_funcs.h"

int	main(int argc, char **argv, char **envp)
{
	(void)argc;	(void)argv;	(void)envp;

	g_data.envp = env_create(envp);
	if (!g_data.envp)
	{
		printf("Can not create local enviroment\n");
		return (1);
	}
	g_data.vars = NULL;
	g_data.exit_status = 0;
}
