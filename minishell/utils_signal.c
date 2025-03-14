/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_signal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoo <aoo@student.42singapore.sg>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:43:30 by aoo               #+#    #+#             */
/*   Updated: 2025/03/14 10:00:50 by aoo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_interrupt(t_core *core)
{
	if (g_sig_interrupt)
	{
		core->status = 130;
		g_sig_interrupt = 0;
		return (130);
	}
	return (0);
}

int	signal_status(int status)
{
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	else if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else
		return (status);
}

int	signal_print(int status)
{
	if (WIFSIGNALED(status))
	{
		status = 128 + WTERMSIG(status);
		if (status == 130 && g_sig_interrupt == 0)
		{
			g_sig_interrupt = 1;
			write(2, "\n", 1);
		}
		else if (status == 131 && g_sig_interrupt == 0)
		{
			g_sig_interrupt = 1;
			write(2, "Quit\n", 5);
		}
	}
	else if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	return (status);
}

int	signal_pipe_exit(int status, t_core *core)
{
	pid_t	pid;

	pid = core->pid;
	if (WIFSIGNALED(status))
	{
		free_core(core);
		kill(pid, WTERMSIG(status));
	}
	else if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	return (status);
}
