/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_branch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 11:40:04 by marvin            #+#    #+#             */
/*   Updated: 2025/01/23 11:40:04 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tokens 	*parse_cmd(t_ast *left_node, t_tokens *whole_list)
{
	int			i;
	int			j;
	t_tokens	*current;

	i = 0;
	j = 0;
	current = whole_list;
	while(current && current->tok_types != T_PIPE)
	{
		if(current->tok_types == T_WORD)
		{
			(left_node->args)[i] = ft_strdup(current->str);
			i++;
		}
		else if(left_node->redirect && (current->tok_types == T_REDIRECT_OUT \
		|| current->tok_types == T_REDIRECT_IN \
		|| current->tok_types == T_APPEND\
		|| current->tok_types == T_HERE_DOCS))
		{
			(left_node->redirect)[j] = ft_strdup(current->str);
			if(current->next->tok_types == T_WORD)
			{
				j++;
				(left_node->redirect)[j] = ft_strdup(current->next->str);
				j++;
				current = current->next;
			}
		}
		current = current->next;
	}
	if(left_node->args)
		(left_node->args)[i] = NULL;
	if(left_node->redirect)
		(left_node->redirect)[j] = NULL;
	return (current);
}
