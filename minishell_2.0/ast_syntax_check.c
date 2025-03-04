/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_syntax_check.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 20:54:08 by nsan              #+#    #+#             */
/*   Updated: 2025/03/04 22:02:59 by marvin           ###   ########.fr       */
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
			printf("minishell: syntax error near unexpected token `newline'\n");
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
		temp->next->tok_types != T_WORD && \
		temp->next->tok_types != T_REDIRECT_IN && \
		temp->next->tok_types != T_HERE_DOCS)
		{
			printf("minishell: syntax error near unexpected token `newline'\n");
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
		if(!temp->next)
		{
			printf("minishell: syntax error near unexpected token `newline'\n");
			return (0);
		}
		if (temp->next->tok_types == T_PIPE)
			return \
			(printf("minishell: syntax error near unexpected token `|'\n"), 0);
		else if (temp->next->tok_types != T_WORD)
		{
			printf("minishell: syntax error near unexpected token `newline'\n");
			return (0);
		}
	}
	return (1);
}

int	check_grammar_syntax(t_tokens *head, char *input)
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
			return (0);
		temp = temp->next;
	}
	return (1);
}
