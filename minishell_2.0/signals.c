<<<<<<< HEAD
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


int g_sig_interruption = 0;

void handle_sigint_heredoc(int sigint)
{
    (void)sigint;
    g_sig_interruption = 1;
    // rl_on_new_line();
    // rl_replace_line("", 0);
    // rl_redisplay();
    close(STDIN_FILENO);
    write(STDOUT_FILENO, "\n", 1);
}

void handle_sigint(int sigint) //handling for the control C
{
    (void)sigint;
    write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void handle_sigint_process(int sigint)
{
    (void)sigint;
    write(STDOUT_FILENO, "\nSIGINT received\n", 17);
    printf("\n");
}

void handle_sigquit_process(int sigint)
{
    (void)sigint;
    write(1, "Quit in sigquit process", 23);
    printf("Quit: %d \n", sigint);
}

void handle_signals()
{
    signal(SIGINT, handle_sigint);
    signal(SIGQUIT, SIG_IGN);
}

// void handle_signals()
// {
//     struct sigaction sa;

//     sa.sa_handler = &handle_sigint;
//     sa.sa_flags = SA_RESTART;
//     sigaction(SIGINT, &handle_sigint, NULL);
//     signal(SIGQUIT, SIG_IGN);
=======
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


int g_sig_interruption = 0;

void handle_sigint_heredoc(int sigint)
{
    (void)sigint;
    g_sig_interruption = 1;
    // rl_on_new_line();
    // rl_replace_line("", 0);
    // rl_redisplay();
    close(STDIN_FILENO);
    write(STDOUT_FILENO, "\n", 1);
}

void handle_sigint(int sigint) //handling for the control C
{
    (void)sigint;
    write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void handle_sigint_process(int sigint)
{
    (void)sigint;
    write(STDOUT_FILENO, "\nSIGINT received\n", 17);
    printf("\n");
}

void handle_sigquit_process(int sigint)
{
    (void)sigint;
    write(1, "Quit in sigquit process", 23);
    printf("Quit: %d \n", sigint);
}

void handle_signals()
{
    signal(SIGINT, handle_sigint);
    signal(SIGQUIT, SIG_IGN);
}

// void handle_signals()
// {
//     struct sigaction sa;

//     sa.sa_handler = &handle_sigint;
//     sa.sa_flags = SA_RESTART;
//     sigaction(SIGINT, &handle_sigint, NULL);
//     signal(SIGQUIT, SIG_IGN);
>>>>>>> 4cdeb0f6219f9fcf8d9941a671c90a0876c7291f
// }