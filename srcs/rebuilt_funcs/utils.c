/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 17:47:57 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/12/19 17:42:35 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/rebuilt_funcs.h"

int	rebuit_is_rebuilt(char *func)
{
	if (!func)
		return (0);
	if (utils_cmp_strings(ECHO, func))
		return (1);
	if (utils_cmp_strings(CD, func))
		return (1);
	if (utils_cmp_strings(PWD, func))
		return (1);
	if (utils_cmp_strings(EXPORT, func))
		return (1);
	if (utils_cmp_strings(UNSET, func))
		return (1);
	if (utils_cmp_strings(ENV, func))
		return (1);
	if (utils_cmp_strings(EXIT, func))
		return (1);
	return (0);
}

// Call rebuilt or original function with [argv[0]] name
void	rebuilt_call_func(int argc, char **argv, int fd_out)
{
	char	*func;

	func = argv[0];
	if (utils_cmp_strings(func, ECHO))
		rebuilt_echo(argc, argv, fd_out);
	else if (utils_cmp_strings(func, CD))
		rebuilt_cd(argc, argv);
	else if (utils_cmp_strings(func, PWD))
		rebuilt_pwd(fd_out);
	else if (utils_cmp_strings(func, EXPORT))
		rebuilt_export(argc, argv, fd_out);
	else if (utils_cmp_strings(func, UNSET))
		rebuilt_unset(argc, argv);
	else if (utils_cmp_strings(func, ENV))
		rebuilt_env(fd_out);
	else if (utils_cmp_strings(func, EXIT))
		rebuilt_exit(argc, argv);
}

int	rebuilt_is_valid_name(char *name)
{
	if (!name || !ft_strlen(name) || (!ft_isalpha(name[0]) && name[0] != '_'))
		return (0);
	name++;
	while (*name)
	{
		if (!ft_isalpha(*name) && !ft_isdigit(*name) && *name != '_')
			return (0);
		name++;
	}
	return (1);
}
