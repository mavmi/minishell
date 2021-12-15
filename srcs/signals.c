/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 13:30:00 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/12/15 13:58:38 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

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

void	par_set_custom_sig(void)
{
	sig_t	sig;

	rl_catch_signals = 0;
	sig = signal(SIGINT, signal_handler);
	if (sig != SIG_IGN)
		g_data.SIG_INT = sig;
	sig = signal(SIGQUIT, SIG_IGN);
	if (sig != SIG_IGN)
		g_data.SIG_QUIT = sig;
}

void	par_set_default_sig(void)
{
	rl_catch_signals = 1;
	signal(SIGINT, g_data.SIG_INT);
	signal(SIGQUIT, g_data.SIG_QUIT);
}

void	par_disable_sig(void)
{
	rl_catch_signals = 0;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
