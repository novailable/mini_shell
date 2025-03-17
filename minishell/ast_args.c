/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsan <nsan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 07:18:09 by nsan              #+#    #+#             */
/*   Updated: 2025/01/14 07:18:09 by nsan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	args_list_len_alloc(t_tokens *whole_list, char ***args_list)
{
	t_tokens	*current;
	int			args_len;

	args_len = 0;
	current = whole_list;
	while (current && current->tok_types != T_PIPE)
	{
		if (current->tok_types == T_WORD)
			args_len++;
		else if (current->tok_types == T_REDIRECT_OUT || \
		current->tok_types == T_REDIRECT_IN || \
		current->tok_types == T_APPEND)
		{
			if (current->next && current->next->tok_types == T_WORD)
				current = current->next;
		}
		current = current->next;
	}
	if (args_len == 0)
		return ((*args_list = NULL), 1);
	*args_list = malloc(sizeof(char *) * (args_len + 1));
	if (!*args_list)
		return (0);
	return (1);
}
