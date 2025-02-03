/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 11:57:07 by marvin            #+#    #+#             */
/*   Updated: 2025/01/16 11:57:07 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	append_token(t_tokens **head, t_tokens *new_node)
{
	t_tokens	*current;

	if (!*head)
	{
		*head = new_node;
		return;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new_node;
}

t_tokens *create_new_token(char *str)
{
	t_tokens *token_malloc;

	token_malloc = malloc(sizeof(t_tokens));
	token_malloc->str = ft_strdup(str);
	token_malloc->next = NULL;	
	return (token_malloc);
}

void	tokenize_str(t_tokens *head)
{
	int i;
	int word;
	char *temp;
	t_tokens *current;
	current = head;
	
	word = 0;
	i = 0;

	while(current)
	{
		temp = current->str;
		i = 0;
		// while(temp[i] != '\0')
		// {
		// 	if ((temp[i] >= 'a' && temp[i] <= 'z') && temp[i+1] == '\0' || (temp[i+1] == '\"'))
		// 	{
		// 		current->tok_types = T_WORD;
		// 		word++;
		// 	}
		// 	i++;
		// }
		if (!ft_strncmp(current->str, "|", 1))
			current->tok_types = T_PIPE;
		else if (!ft_strncmp(current->str, ">>", 2))
			current->tok_types = T_APPEND;
		else if (!ft_strncmp(current->str, "<<", 2))
			current->tok_types = T_HERE_DOCS;
		else if (!ft_strncmp(current->str, ">", 1))
			current->tok_types = T_REDIRECT_OUT;
		else if (!ft_strncmp(current->str, "<", 1))
			current->tok_types = T_REDIRECT_IN;
		else
			current->tok_types = T_WORD;
		current = current->next;
	}
}
