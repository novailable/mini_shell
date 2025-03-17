/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoo <aoo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:26:58 by nsan              #+#    #+#             */
/*   Updated: 2025/03/16 18:18:52 by aoo              ###   ########.fr       */
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

t_tokens	*create_new_token(char *str, int type)
{
	t_tokens	*token_malloc;

	token_malloc = malloc(sizeof(t_tokens));
	if (!token_malloc)
		return (printf("token creation\n"), NULL);
	token_malloc->str = ft_strdup(str);
	token_malloc->tok_types = type;
	token_malloc->next = NULL;
	return (token_malloc);
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
