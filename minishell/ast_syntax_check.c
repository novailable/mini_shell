/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_syntax_check.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsan <nsan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 20:54:08 by nsan              #+#    #+#             */
/*   Updated: 2025/03/10 16:20:32 by nsan             ###   ########.fr       */
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
		(temp->next->tok_types != T_WORD && \
		temp->next->tok_types != T_REDIRECT_IN && \
		temp->next->tok_types != T_REDIRECT_OUT && \
		temp->next->tok_types != T_HERE_DOCS))
			return (print_err_msg(ERR_QUOTE, "newline", "'\n"), 0);
	}
	return (1);
}

int	syntax_redirect_error(t_tokens *temp)
{
	if (temp->tok_types == T_REDIRECT_IN || \
		temp->tok_types == T_HERE_DOCS || \
		temp->tok_types == T_REDIRECT_OUT || \
		temp->tok_types == T_APPEND)
	{
		if (!temp->next)
			return (print_err_msg(ERR_QUOTE, "newline", "'\n"), 0);
		else if (temp->next->tok_types != T_WORD && \
				temp->next->tok_types != T_REDIRECT_OUT)
			return (print_err_msg(ERR_QUOTE, temp->next->str, "'\n"), 0);
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
			return (0);
		temp = temp->next;
	}
	return (1);
}
