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

void	redirect_list_len_alloc(t_tokens *whole_list, char ***redirect_list)
{
	t_tokens	*current;
	int			redirect_len;

	redirect_len = 0;
	current = whole_list;
	while (current && current->tok_types != T_PIPE)
	{
		if (current->tok_types == T_REDIRECT_OUT \
		|| current->tok_types == T_REDIRECT_IN \
		|| current->tok_types == T_HERE_DOCS \
		|| current->tok_types == T_APPEND)
		{
			if (current->next->tok_types == T_WORD)
			{
				redirect_len += 2;
				current = current->next;
			}
		}
		current = current->next;
	}
	if (redirect_len == 0)
	{
		*redirect_list = NULL;
		return ;
	}
	*redirect_list = malloc(sizeof(char *) * (redirect_len + 1));
}

// t_ast	*redirection_list(t_ast *node, t_tokens **whole_list)
// {
// 	char	**redirect_list;

// 	redirect_list_len_alloc(whole_list, &redirect_list);
// 	if (redirect_list != NULL)
// 		node->cmd = parse_cmd(&redirect_list, whole_list, 0);
// 	else
// 		node->cmd = NULL;
// 	return (node);
// }
