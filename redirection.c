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

char	*get_heredoc(char *eof, t_list *envp, int status)
{
	char	*line;
	char	*temp;

	temp = NULL;
	while (1)
	{
		set_signal_heredoc();
		line = readline("> ");
		if (g_sig_interrupt)
			return (free(temp), free(eof), NULL);
		if (!line)
		{
			ft_putstr_fd("minishell: warning: here-document delimited by end-of-file (wanted `", STDERR_FILENO);
			ft_putstr_fd(eof, STDERR_FILENO);
			ft_putstr_fd("')\n", STDERR_FILENO);
			break;
		}
		if (ft_strcmp(line, eof) == 0)
		{
			free(line);
			break;
		}
		temp = ft_strjoin(temp, handle_env(line, envp, status), 1, 1);
		temp = ft_strcjoin(temp, '\n');
		free(line);
	}
	free(eof);
	return (temp);
}


// Apply redirections using the prepared heredocs
int redirection(char **redirect)
{
	int	in_fd;
	int	i;

    i = 0;
	in_fd = -1;
    while (redirect && redirect[i])
    {
        in_fd = redirection_in_heredoc(redirect, i, in_fd);
        i++;
    }
    i = 0;
    while (redirect[i])
    {
        redirection_out_append(redirect, i, in_fd);
        i++;
    }
    if (in_fd > 0)
        (dup2(in_fd, STDIN_FILENO), close(in_fd));
    return 0;
}

