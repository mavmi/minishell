/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 12:43:10 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/09/11 13:12:48 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/rebuilt_funcs.h"

void	my_echo(int argc, char **argv)
{
	int	i;
	int	endl;

	if (argc < 1)
		return ;
	i = 1;
	endl = 1;
	if (cmp_strings(argv[i], "-n"))
	{
		endl = 0;
		i++;
	}
	while (i < argc)
	{
		printf("%s", argv[i]);
		if (i != argc - 1)
			printf(" ");
		i++;
	}
	if (endl)
		printf("\n");
}