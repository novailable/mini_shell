/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_branch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsan <nsan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 17:29:40 by nsan              #+#    #+#             */
/*   Updated: 2025/03/11 17:29:40 by nsan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_redirect_type(int tok_type)
{
	return (tok_type == T_REDIRECT_IN || tok_type == T_REDIRECT_OUT
		|| tok_type == T_APPEND || tok_type == T_HERE_DOCS);
}

t_tokens	*parse_cmd(t_ast *left_node, t_tokens *whole_list)
{
	int			i;
	int			j;
	t_tokens	*current;

	i = 0;
	j = 0;
	current = whole_list;
	while (current && current->tok_types != T_PIPE)
	{
		if (left_node->args && current->tok_types == T_WORD)
			(left_node->args)[i++] = ft_strdup(current->str);
		else if (left_node->redirect && is_redirect_type(current->tok_types))
		{
			(left_node->redirect)[j++] = ft_strdup(current->str);
			if (current->next && current->next->tok_types == T_WORD)
				(left_node->redirect)[j++] = \
				ft_strdup((current = current->next)->str);
		}
		current = current->next;
	}
	if (left_node->args)
		(left_node->args)[i] = NULL;
	if (left_node->redirect)
		(left_node->redirect)[j] = NULL;
	return (current);
}
