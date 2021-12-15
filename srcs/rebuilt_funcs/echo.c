/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 12:43:10 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/12/15 18:56:16 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/rebuilt_funcs.h"

static int	is_flag(char *str)
{
	if (!str || !ft_strlen(str) || *str != '-')
		return (0);
	str++;
	while (*str)
	{
		if (*str != 'n')
			return (0);
		str++;
	}
	return (1);
}

void	rebuilt_echo(int argc, char **argv, int fd_out)
{
	int	i;
	int	endl;

	if (argc < 1)
		return ;
	i = 1;
	endl = 1;
	if (is_flag(argv[i]))
	{
		endl = 0;
		i++;
	}
	while (i < argc)
	{
		ft_putstr_fd(argv[i], fd_out);
		if (i != argc - 1)
			ft_putstr_fd(" ", fd_out);
		i++;
	}
	if (endl)
		ft_putendl_fd("", fd_out);
	g_data.exit_status = 0;
}
