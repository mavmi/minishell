/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 15:54:30 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/11/12 12:59:22 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/rebuilt_funcs.h"

// Get command string [char *command] from terminal
// and split by spaces into [char **argv]
void	parse_command(char *command)
{
	int		argc;
	char	**tmp_ptr;
	char	**command_strs;

	command_strs = ft_split(command, ' ');
	if (!command_strs || !ft_strlen(command)){
		utils_destroy_strings_array(command_strs);
		return ;
	}
	argc = 0;
	tmp_ptr = command_strs;
	while (*tmp_ptr)
	{
		argc++;
		tmp_ptr++;
	}
	rebuilt_call_func(argc, command_strs, /* заглушка */ STDOUT_FILENO);
	utils_destroy_strings_array(command_strs);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc; (void)argv; (void)envp;
}
