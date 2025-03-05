/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 18:14:31 by nsan              #+#    #+#             */
/*   Updated: 2025/03/05 14:54:43 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	re_input(char *file)
{
	int	fd_in;

	if (file && !access(file, F_OK | R_OK))
	{
		fd_in = open(file, O_RDONLY);
		if (fd_in > 0)
			return (fd_in);
	}
	write(2, "minishell: ", 12);
	write(2, file, ft_strlen(file));
	perror(" ");
	return (-1);
}

int	re_output(char *file, int append)
{
	int	fd_out;

	if (append)
		fd_out = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd_out = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out < 0)
	{
		write(2, "minishell: ", 12);
		write(2, file, ft_strlen(file));
		perror(" ");
		return (-1);
	}
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
	return (0);
}

int	re_heredoc(char *data)
{
	int		fd_pipe[2];

	if (pipe(fd_pipe) == -1)
		return (perror("pipe error"), -1);
	write(fd_pipe[1], data, ft_strlen(data));
	return (close(fd_pipe[1]), fd_pipe[0]);
}

int	redirection_in_heredoc(char **redirect, int i, int in_fd)
{
	if (!ft_strcmp(redirect[i], "<") && redirect[i + 1])
	{
		if (in_fd > 0)
			close(in_fd);
		in_fd = re_input(redirect[++i]);
		if (in_fd == -1)
			return (-1);
	}
	else if (!ft_strcmp(redirect[i], "<<") && redirect[i + 1])
	{
		if (in_fd > 0)
			close(in_fd);
		in_fd = re_heredoc(redirect[++i]);
		if (in_fd == -1)
			return (-1);
	}
	return (in_fd);
}

int	redirection_out_append(char **redirect, int i, int in_fd)
{
	if (!ft_strcmp(redirect[i], ">") && redirect[i + 1])
	{
		if (re_output(redirect[++i], 0) == -1)
			return (-1);
	}
	else if (!ft_strcmp(redirect[i], ">>") && redirect[i + 1])
	{
		if (re_output(redirect[++i], 1) == -1)
			return (-1);
	}
	return (in_fd);
}
