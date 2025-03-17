/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsan <nsan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 02:09:16 by nsan              #+#    #+#             */
/*   Updated: 2025/01/14 02:09:16 by nsan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	iterate_list(t_tokens *whole_list, int *redirect_len)
{
	t_tokens	*current;

	current = whole_list;
	while (current && current->tok_types != T_PIPE)
	{
		if (current->tok_types == T_REDIRECT_IN && \
			current->next && current->next->tok_types == T_REDIRECT_OUT)
			*redirect_len += 1;
		else if (current->tok_types == T_REDIRECT_OUT \
		|| current->tok_types == T_REDIRECT_IN \
		|| current->tok_types == T_HERE_DOCS \
		|| current->tok_types == T_APPEND)
		{
			if (current->next && current->next->tok_types == T_WORD)
			{
				*redirect_len += 2;
				current = current->next;
			}
		}
		current = current->next;
	}
}

int	redirect_list_len_alloc(t_tokens *whole_list, char ***redirect_list)
{
	int			redirect_len;

	redirect_len = 0;
	iterate_list(whole_list, &redirect_len);
	if (redirect_len == 0)
	{
		*redirect_list = NULL;
		return (1);
	}
	*redirect_list = malloc(sizeof(char *) * (redirect_len + 1));
	if (!*redirect_list)
		return (0);
	return (1);
}
