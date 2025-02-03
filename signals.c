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

//need to kill the child if control+z is hit
//recall new readline if control+c is hit

void control_c(int sigint)
{
    (void)sigint;
    printf("\n");
	rl_on_new_line();
	rl_replace_line(" ", 0);
	rl_redisplay();
}

void signal_handling()
{
    struct sigaction sa;

    sa.sa_handler = &control_c;
    sa.sa_flags = SA_RESTART;
    sigaction(SIGINT, &sa, NULL);

    signal(SIGQUIT, SIG_IGN);

}