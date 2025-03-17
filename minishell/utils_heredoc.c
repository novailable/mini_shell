/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoo <aoo@student.42singapore.sg>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 20:42:22 by aoo               #+#    #+#             */
/*   Updated: 2025/03/17 13:13:46 by aoo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_dollar(char *start, int q_end)
{
	int		i;
	int		all_dollar;
	char	*result;

	i = 0;
	result = NULL;
	all_dollar = 0;
	while (start[i] && start[i] == '$')
	{
		if (start[i + 1] == '\0')
			all_dollar = 1;
		i++;
	}
	if (!q_end || !all_dollar)
		return (ft_strdup(start));
	i = i - (i % 2);
	while (i--)
		result = ft_strcjoin(result, '$');
	return (result);
}

char	*get_eof(char *eof, int quote)
{
	char	*result;
	char	*temp;
	int		i;

	if (!quote)
		return (handle_quotes(eof));
	i = 0;
	temp = eof;
	result = NULL;
	while (eof[i])
	{
		if (eof[i] == '$')
		{
			temp = eof + i;
			while (eof[i] && !ft_strchr("\"\'", eof[i]))
				i++;
			temp = ft_strndup(temp, eof + i - temp);
			result = ft_strjoin(result, handle_dollar(temp, (eof[i] == '\"' \
													|| eof[i] == '\'')), 1, 1);
			free(temp);
		}
		else
			result = ft_strcjoin(result, eof[i++]);
	}
	return (temp = handle_quotes(result), free(result), temp);
}

char	*get_heredoc(char *eof, int quote)
{
	char	*line;
	char	*temp;
	char	*q_eof;

	temp = ft_strdup("");
	q_eof = get_eof(eof, quote);
	free(eof);
	while (1)
	{
		if (g_sig_interrupt)
			return (free(temp), free(q_eof), NULL);
		set_signal_heredoc();
		line = readline("> ");
		(signal(SIGINT, SIG_IGN), signal(SIGQUIT, SIG_IGN));
		if (!line && print_heredoc_err(q_eof))
			break ;
		if (ft_strcmp(line, q_eof) == 0)
		{
			free(line);
			break ;
		}
		temp = ft_strjoin(temp, line, 1, 1);
		temp = ft_strcjoin(temp, '\n');
	}
	return (rl_event_hook = NULL, free(q_eof), temp);
}

void	erase_quote(t_tokens *current)
{
	char	*temp;

	temp = current->str;
	current->str = handle_quotes(temp);
	free(temp);
}

void	prepare_heredoc(t_core *core)
{
	t_tokens	*current;
	char		*temp;
	int			quote;

	current = core->tokens;
	while (current)
	{
		if (current->tok_types == T_HERE_DOCS && current->next && \
			current->next->tok_types == T_WORD)
		{
			current = current->next;
			quote = ft_strchr(current->str, '\"') || \
					ft_strchr(current->str, '\'');
			current->str = get_heredoc(current->str, quote);
			if (current->str && *current->str && !quote)
			{
				temp = current->str;
				current->str = handle_env(current->str, core);
				free(temp);
			}
		}
		else
			erase_quote(current);
		current = current->next;
	}
}
