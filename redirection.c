/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 19:08:12 by aoo               #+#    #+#             */
/*   Updated: 2025/02/24 17:39:53 by aoo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	re_input(char *file)
{
	int	fd_in;

	if (file && !access(file, F_OK | R_OK))
	{
		fd_in = open(file, O_RDONLY);
		dprintf(2, "re_input, in : %d\n", fd_in);
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
	printf("out : %d\n",fd_out);
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

int	re_heredoc(char *args, t_list *envp, int status)
{
	char	*line;
	int		fd_pipe[2];
	char	*temp;

	if (pipe(fd_pipe) == -1)
		return (perror("pipe error"), -1);
	signal(SIGINT, handle_sigint_heredoc);
	// signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		line = readline("> ");
		if(g_sig_interruption)
		{
			close(fd_pipe[1]);
			return (-1);
		}
		if (!line || ft_strcmp(line, args) == 0)
		{
			free(line); 
			break ;
		}
		temp = handle_env(line, envp, status);
		(write(fd_pipe[1], temp, ft_strlen(temp)), write(fd_pipe[1], "\n", 1));
		(free(line), free(temp));
	}
	return (close(fd_pipe[1]), fd_pipe[0]);
}
int	redirection(char **redirect, t_list *envp, int status)
{
	int	i;
	int here_fd;
	int	in_fd;
	int out_fd;

	i = 0;
	here_fd = -1;
	in_fd = -1;
	out_fd = -1;
	while (redirect[i])
	{
		if (!ft_strcmp(redirect[i], "<<") && redirect[++i])
		{
			if (here_fd > 0)
				close (here_fd);
			here_fd = re_heredoc(redirect[i], envp, status);
		}
		i++;
	}
	i = 0;
	while (redirect[i])
	{
		if (!ft_strcmp(redirect[i], "<") && redirect[++i])
		{
			if (in_fd > 0)
				close(in_fd);
			in_fd = re_input(redirect[i]);
			if (in_fd == -1)
				return (-1);
		}
		else if (!ft_strcmp(redirect[i], "<<") && redirect[++i])
			in_fd = here_fd;
		i++;
	}
	i=0;
	while (redirect[i])
	{
		if (!ft_strcmp(redirect[i], ">>") && redirect[++i])
		{
			if (re_output(redirect[i], 1) == -1)
				return (-1);
		}
		else if (!ft_strcmp(redirect[i], ">") && redirect[++i])
		{
			if (re_output(redirect[i], 0) == -1)
				return (-1);
		}
		i++;
	}
	if (in_fd > 0)
		(dup2(in_fd, STDIN_FILENO), close(in_fd));
	return (0);
}
