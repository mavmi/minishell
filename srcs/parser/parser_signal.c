/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 13:30:00 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/12/16 14:59:03 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

// Signals call this function
static void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		printf("\n");
		rl_redisplay();
	}
}

void	par_sig_init(void)
{
	rl_catch_signals = 0;
	g_data.SIG_INT = signal(SIGINT, signal_handler);
	g_data.SIG_QUIT = signal(SIGQUIT, SIG_IGN);
}

void	par_set_custom_sig(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	par_set_default_sig(void)
{
	signal(SIGINT, g_data.SIG_INT);
	signal(SIGQUIT, g_data.SIG_QUIT);
}

void	par_disable_sig(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
