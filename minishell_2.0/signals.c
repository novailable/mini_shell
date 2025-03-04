/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 18:37:37 by marvin            #+#    #+#             */
/*   Updated: 2025/01/29 18:37:37 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_sig_interrupt = 0;

void	handle_sigint_heredoc(int sigint)
{
	(void)sigint;
	g_sig_interrupt = 1;
	rl_event_hook = NULL;
	rl_done = 1;
}

int	check_signal(void)
{
	if (!g_sig_interrupt)
		return (0);
	rl_done = 1;
	return (1);
}

void	set_signal_heredoc(void)
{
	signal(SIGINT, &handle_sigint_heredoc);
	signal(SIGQUIT, SIG_IGN);
	rl_event_hook = check_signal;
}

void handle_sigint(int sigint)
{
	(void)sigint;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

// void handle_sigint_process(int sigint)
// {
//     (void)sigint;
//     write(STDOUT_FILENO, "\nSIGINT received\n", 17);
//     printf("\n");
// }

// void handle_sigquit_process(int sigint)
// {
//     (void)sigint;
//     write(1, "Quit in sigquit process", 23);
//     printf("Quit: %d \n", sigint);
// }

// void handle_signals()
// {
//     signal(SIGINT, handle_sigint);
//     signal(SIGQUIT, SIG_IGN);
// }

void	set_signal(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	stop_signal(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	default_signal(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

int	wait_signal_status(int status)
{
	int	signal;

	if (WIFSIGNALED(status))
	{
		signal = WTERMSIG(status);
		if (signal == SIGINT)
			ft_putstr_fd("\n", 2);
		else if (signal == SIGQUIT)
			ft_putstr_fd("Quit\n", 2);
		return (128 + WTERMSIG(status));
	}
	else if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (status);
}
// void handle_signals()
// {
//     struct sigaction sa;

//     sa.sa_handler = &handle_sigint;
//     sa.sa_flags = SA_RESTART;
//     sigaction(SIGINT, &handle_sigint, NULL);
//     signal(SIGQUIT, SIG_IGN);
// }