/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_syntax_check.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsan <nsan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 20:54:08 by nsan              #+#    #+#             */
/*   Updated: 2025/01/28 21:00:13 by nsan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	syntax_word_error(t_tokens *temp)
{
	if (temp->tok_types == T_WORD)
	{
		if (temp->next->tok_types != T_WORD && \
			temp->next->tok_types != T_PIPE && \
			temp->next->tok_types != T_REDIRECT_IN && \
			temp->next->tok_types != T_APPEND && \
			temp->next->tok_types != T_REDIRECT_OUT && \
			temp->next->tok_types != T_HERE_DOCS)
		{
			printf("Invalid syntax after T_WORD\n");
			return (0);
		}
	}
	return (1);
}

int	syntax_pipe_error(t_tokens *temp)
{
	if (temp->tok_types == T_PIPE)
	{
		if (temp->next == NULL || \
		temp->next->tok_types != T_WORD)
		{
			printf("Invalid syntax after T_PIPE\n");
			return (0);
		}
	}
	return (1);
}

int	syntax_redirect_error(t_tokens *temp)
{
	if (temp->tok_types == T_REDIRECT_IN || \
	temp->tok_types == T_REDIRECT_OUT || \
	temp->tok_types == T_APPEND || \
	temp->tok_types == T_HERE_DOCS)
	{
		if (temp->next == NULL || temp->next->tok_types != T_WORD)
		{
			printf("Invalid syntax after redirect\n");
			return (0);
		}
	}
	return (1);
}

int	check_grammar_syntax(t_tokens *head)
{
	t_tokens	*temp;

	temp = head;
	while (temp)
	{
		if (temp->tok_types == T_WORD && temp->next == NULL)
			return (1);
		if (syntax_word_error(temp) == 0 || \
		syntax_pipe_error(temp) == 0 || \
		syntax_redirect_error(temp) == 0)
			return (0); //on error
		temp = temp->next;
	}
	return (1);
}

// if (!whole_list || !*whole_list)
//     {
//         printf("Invalid input: whole_list is NULL\n");
//         return (0);
//     }