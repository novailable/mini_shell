/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoo <aoo@student.42singapore.sg>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 19:08:12 by aoo               #+#    #+#             */
/*   Updated: 2025/02/03 09:01:40 by aoo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	re_input(char *file, t_list *envp)
{
	int	fd_in;

	// file = first_processing(file, envp);
	if (file && !access(file, F_OK | R_OK))
	{
		fd_in = open(file, O_RDONLY);
		if (fd_in < 0)
		{
			write (2, file, ft_strlen(file));
			perror("error opening");
			return (-1);
		}
	}
	// free(file);
	return (fd_in);
}

void	re_output(char *file, t_list *envp, int append)
{
	int	fd_out;

	// file = first_processing(file, envp);
	if (append)
		fd_out = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd_out = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out < 0)
	{
		write(2, file, ft_strlen(file));
		perror("error opening");
		free(file);
		return ;
	}
	dup2(fd_out, STDOUT_FILENO);
	// free(file);
	close(fd_out);
}

int	app_heredoc(char *args)
{
	char	*line;
	int		fd_pipe[2];
	char	*eof;

	eof = heredoc_processing(args);
	if (pipe(fd_pipe) == -1)
	{
		perror("pipe error");
		return (free(eof), -1);
	}
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, eof) == 0)
		{
			free(line);
			break ;
		}
		write(fd_pipe[1], line, ft_strlen(line));
		write(fd_pipe[1], "\n", 1);
		free(line);
	}
	close(fd_pipe[1]);
	free(eof);
	return (fd_pipe[0]);
}

void	redirection(char **redirect, t_list	*envp)
{
	int		in_fd;

	in_fd = -1;
	while (*redirect)
	{
		if (in_fd > 0)
		{
			close(in_fd);
			in_fd = -1;
		}
		if (!ft_strcmp(*redirect, "<") && *(++redirect))
			in_fd = re_input(*redirect, envp);
		else if (!ft_strcmp(*redirect, "<<") && *(++redirect))
			in_fd = app_heredoc(*redirect);
		else if (!ft_strcmp(*redirect, ">") && *(++redirect))
			re_output(*redirect, envp, 0);
		else if (!ft_strcmp(*redirect, ">>") && *(++redirect))
			re_output(*redirect, envp, 1);
		redirect++;
	}
	if (in_fd > 0)
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
		in_fd = -1;
	}
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
