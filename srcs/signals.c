/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 21:07:21 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/09/08 21:23:08 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	signal_handler(int sig)
{
	if (sig == SIGINT)			// ctrl + C
		printf("CTRL + C\n");
	else if (sig == SIGQUIT) 	// ctrl + /
		printf("CTRL + \\\n");
}

void	set_up_signals(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
}
