/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoo <aoo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 18:14:31 by nsan              #+#    #+#             */
/*   Updated: 2025/03/12 18:03:01 by aoo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	re_input(char *file, int *in_fd)
{
	int	fd_in;

	if (file && !access(file, F_OK | R_OK))
	{
		fd_in = open(file, O_RDONLY);
		if (fd_in > 0)
			return (*in_fd = fd_in, 1);
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

int	re_heredoc(char *data, int *in_fd)
{
	int		fd_pipe[2];

	if (pipe(fd_pipe) == -1)
		return (perror("pipe error"), -1);
	if (data)
		write(fd_pipe[1], data, ft_strlen(data));
	close(fd_pipe[1]);
	*in_fd = fd_pipe[0];
	return (1);
}

int	re_spec_in(char *file, int *in_fd)
{
	struct stat	st;

	if (stat(file, &st) == 0 && S_ISDIR(st.st_mode))
	{
		print_err_msg(file, ": Is a directory\n", NULL);
		return (-1);
	}
	*in_fd = open(file, O_RDWR | O_CREAT, 0644);
	if (*in_fd < -1)
		return (print_err_msg(file, NULL, NULL), perror (" "), -1);
	return (0);
}
