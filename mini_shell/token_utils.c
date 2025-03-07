/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoo <aoo@student.42singapore.sg>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:26:58 by nsan              #+#    #+#             */
/*   Updated: 2025/03/07 18:15:09 by aoo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	append_token(t_tokens **head, t_tokens *new_node)
{
	t_tokens	*current;

	if (!*head)
	{
		*head = new_node;
		return ;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new_node;
}

t_tokens	*create_new_token(char *str)
{
	t_tokens	*token_malloc;

	token_malloc = malloc(sizeof(t_tokens));
	token_malloc->str = ft_strdup(str);
	token_malloc->next = NULL;
	return (token_malloc);
}

void	prepare_heredoc(t_core *core)
{
	t_tokens	*current;
	char		*temp;
	char		*quote;

	current = core->tokens;
	while (current)
	{
		if (current->tok_types == T_HERE_DOCS && current->next && \
			current->next->tok_types == T_WORD)
		{
			current = current->next;
			quote = ft_strchr("\"\'", *current->str);
			current->str = get_heredoc(current->str, core->envp, core->status);
			if (!quote)
			{
				temp = current->str;
				current->str = handle_env(current->str, core);
				free(temp);
			}
		}
		else
		{
			temp = current->str;
			current->str = handle_quotes(temp);
			free(temp);
		}
		current = current->next;
	}
}

void	tokenize_str(t_tokens *head)
{
	t_tokens	*current;

	current = head;
	while (current)
	{
		if (!ft_strcmp(current->str, "|"))
			current->tok_types = T_PIPE;
		else if (!ft_strcmp(current->str, ">>"))
			current->tok_types = T_APPEND;
		else if (!ft_strcmp(current->str, "<<"))
			current->tok_types = T_HERE_DOCS;
		else if (!ft_strcmp(current->str, ">"))
			current->tok_types = T_REDIRECT_OUT;
		else if (!ft_strcmp(current->str, "<"))
			current->tok_types = T_REDIRECT_IN;
		else
			current->tok_types = T_WORD;
		current = current->next;
	}
}
