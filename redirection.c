/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoo <aoo@student.42singapore.sg>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 19:08:12 by aoo               #+#    #+#             */
/*   Updated: 2025/02/24 12:28:12 by aoo              ###   ########.fr       */
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

int	re_output(char **redirect)
{
	int	fd_out;

	while (*redirect)
	{
		if (!ft_strcmp(*redirect, ">>") && *(++redirect))
			fd_out = open(*redirect, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else if (!ft_strcmp(*redirect, ">") && *(++redirect))
			fd_out = open(*redirect, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd_out < 0)
		{
			write(2, *redirect, ft_strlen(*redirect));
			perror("error opening");
			return (-1);
		}
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
		redirect++;
	}
	return (0);
}

int	re_heredoc(char *args, t_list *envp, int status)
{
	char	*line;
	int		fd_pipe[2];
	char	*temp;

	if (pipe(fd_pipe) == -1)
		return (perror("pipe error"), -1);
	while (1)
	{
		line = readline("> ");
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

// int	redirection(char **redirect, t_list	*envp, int status)
// {
// 	int		in_fd;

// 	in_fd = 0;
// 	while (*redirect)
// 	{
// 		if (!ft_strcmp(*redirect, "<") && *(++redirect))
// 			in_fd = re_input(*redirect, envp);
// 		else if (!ft_strcmp(*redirect, "<<") && *(++redirect))
// 			in_fd = re_heredoc(*redirect, envp, status);
// 		else if (!ft_strcmp(*redirect, ">") && *(++redirect))
// 			re_output(*redirect, envp, 0);
// 		else if (!ft_strcmp(*redirect, ">>") && *(++redirect))
// 			re_output(*redirect, envp, 1);
// 		redirect++;
// 	}
// 	dprintf(2, "in_fd %d\n", in_fd);
// 	if (in_fd > 0)
// 		(dup2(in_fd, STDIN_FILENO), close(in_fd));
// 	else if (in_fd == -1)
// 		return (-1);
// 	return (0);
// }

int	re_input_fd(char **redirect, int here_fd)
{
	int	in_fd;

	in_fd = 0;
	
	while (*redirect)
	{
		if (in_fd)
			close(in_fd);
		if (!ft_strcmp(*redirect, "<") && *(++redirect))
			in_fd = re_input(*redirect);
		else if (!ft_strcmp(*redirect, "<<") && *(++redirect))
			in_fd = here_fd;
		if (in_fd == -1)
			return (-1);
		redirect++;
	}
	if (in_fd > 0)
		(dup2(in_fd, STDIN_FILENO), close(in_fd));
	return (0);
}

int	redirection(char **redirect, t_list	*envp, int status)
{
	int		i;
	int		here_fd;

	here_fd = 0;
	i = 0;
	while (redirect[i])
	{
		if (here_fd > 0)
			close (here_fd);
		if (!ft_strcmp(redirect[i], "<<") && redirect[++i])
			here_fd = re_heredoc(redirect[i], envp, status);
		i++;
	}
	if (re_input_fd(redirect, here_fd) == -1 || re_output(redirect) == -1)
		return (-1);
	return (0);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	char *input = readline("%% ");
// 	char *in;
// 	int		fd;
// 	char *file;
// 	pid_t pid;
// 	int		heredoc_fd[2];
// 	int     org_fd[2];

// 	org_fd[0] = dup(STDIN_FILENO);
// 	org_fd[1] = dup(STDOUT_FILENO);

// 	if (!input)
// 		return 0;

// 	fd = -1;
// 	in = strtok(input, " ");
// 	while (in)
// 	{
// 		if (fd > 0)
// 		{
// 			close(fd);
// 			fd = -1;
// 		}
// 		if (strcmp(in, "<") == 0)
// 		{
// 			file = strtok(NULL, " ");
// 			if (file)
// 			{
// 				printf("file: %s\n", file);
// 				fd = re_input(file);
// 			}
// 		}
// 		else if (strcmp(in, "<<") == 0)  // Check for heredoc operator
// 		{
// 			file = strtok(NULL, " ");
// 			if (file)
// 			{
// 				printf("heredoc EOF: %s\n", file);
// 				fd = app_heredoc (file);
// 			}
// 		}
// 		else if (strcmp(in, ">") == 0)
// 		{
// 			file = strtok(NULL, " ");
// 			if (file)
// 			{
// 				printf("out file : %s\n", file);
// 				re_output(file, 0);
// 			}
// 		}

// 		in = strtok(NULL, " ");
// 	}
// 	char buffer[2000];
// 	if (fd > 0)
// 	{
// 		dup2(fd, STDIN_FILENO);
// 		close(fd);
// 		fd = -1;
// 	}
// 	size_t n = read(STDIN_FILENO, buffer, sizeof(buffer) + 1);
// 	buffer[n] = '\0';
// 	re_output("ok", 0);
// 	re_output("ok2", 0);
//    	printf("buffer: %s\n", buffer);
// 	return 0;
// }
