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

// char	*get_heredoc(char *eof, t_list *envp, int status)
// {
// 	char	*line;
// 	char	*temp;
// 	int		env_replace;
	
// 	env_replace = 0;
// 	if ()
// 	temp = NULL;
// 	while (1)
// 	{
// 		set_signal_heredoc();
// 		line = readline("> ");
// 		if (g_sig_interrupt)
// 			return (free(temp), free(eof), NULL);
// 		if (!line)
// 		{
// 			print_heredoc_err(eof);
// 			break ;
// 		}
// 		if (ft_strcmp(line, eof) == 0)
// 		{
// 			free(line);
// 			break ;
// 		}
// 		temp = ft_strjoin(temp, handle_env(line, envp, status), 1, 1);
// 		temp = ft_strcjoin(temp, '\n');
// 		free(line);
// 	}
// 	free(eof);
// 	return (temp);
// }

char	*get_heredoc(char *eof, t_list *envp, int status)
{
	char	*line;
	char	*temp;
	char	*q_eof;

	temp = NULL;
	q_eof = handle_quotes(eof);
	free(eof);
	while (1)
	{
		set_signal_heredoc();
		line = readline("> ");
		if (g_sig_interrupt)
			return (free(temp), free(q_eof), NULL);
		if (!line)
		{
			print_heredoc_err(q_eof);
			break ;
		}
		if (ft_strcmp(line, q_eof) == 0)
		{
			free(line);
			break ;
		}
		temp = ft_strcjoin(line, '\n');
	}
	rl_event_hook = NULL;
	free(q_eof);
	return (temp);
}

int	redirection(char **redirect)
{
	int	in_fd;
	int	i;

	i = 0;
	in_fd = -1;
	while (redirect && redirect[i])
	{
		in_fd = redirection_in_heredoc(redirect, i, in_fd);
		if (in_fd == -1)
			return (-1);
		i++;
	}
	i = 0;
	while (redirect[i])
	{
		if (redirection_out_append(redirect, i, in_fd) == -1)
			return (-1);
		i++;
	}
	if (in_fd > 0)
		(dup2(in_fd, STDIN_FILENO), close(in_fd));
	return (0);
}
