/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoo <aoo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 18:06:53 by aoo               #+#    #+#             */
/*   Updated: 2025/03/12 18:06:53 by aoo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_in(char **redirect, int *in_fd)
{
	if (!ft_strcmp(*redirect, "<"))
	{
		if (*in_fd > 0)
			close(*in_fd);
		if (*(redirect + 1) && re_input(*(redirect + 1), in_fd) == -1)
			return (-1);
	}
	else if (!ft_strcmp(*redirect, "<<"))
	{
		if (*in_fd > 0)
			close(*in_fd);
		if (re_heredoc(*(redirect + 1), in_fd) == -1)
			return (-1);
	}
	return (0);
}

int	handle_out(char **redirect)
{
	if (!ft_strcmp(*redirect, ">") && *(redirect + 1))
	{
		if (re_output(*(++redirect), 0) == -1)
			return (-1);
	}
	else if (!ft_strcmp(*redirect, ">>") && *(redirect + 1))
	{
		if (re_output(*(++redirect), 1) == -1)
			return (-1);
	}
	return (0);
}

int	redirection(char **redirect)
{
	int	in_fd;

	in_fd = -1;
	while (redirect && *redirect)
	{
		if (!ft_strcmp(*redirect, "<") && *(redirect + 1)
			&& !ft_strcmp(*(redirect + 1), ">"))
		{
			redirect += 2;
			if (re_spec_in(*redirect, &in_fd) == -1)
				return (-1);
		}
		if (handle_in(redirect, &in_fd) == -1)
			return (-1);
		if (handle_out(redirect) == -1)
			return (-1);
		redirect++;
	}
	if (in_fd > 0)
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
	return (0);
}
