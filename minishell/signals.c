/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsan <nsan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 17:30:03 by nsan              #+#    #+#             */
/*   Updated: 2025/03/11 17:30:03 by nsan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_sig_interrupt = 0;

void	handle_sigint(int sigint)
{
	(void)sigint;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_sig_interrupt = 1;
}

void	handle_sigint_heredoc(int sigint)
{
	(void)sigint;
	g_sig_interrupt = 1;
	rl_event_hook = NULL;
	rl_done = 1;
}

static int	check_sigint(void)
{
	if (g_sig_interrupt)
	{
		rl_done = 1;
		return (1);
	}
	return (0);
}

void	set_signal_heredoc(void)
{
	signal(SIGINT, &handle_sigint_heredoc);
	signal(SIGQUIT, SIG_IGN);
	rl_event_hook = check_sigint;
}
