/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 02:28:23 by nsan              #+#    #+#             */
/*   Updated: 2025/01/16 11:34:51 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*ast(t_ast *ast_node, t_tokens *whole_list)
{
	t_tokens	*ptr;

	if (!whole_list)
		return (ast_node);
	if (!ast_node)
		printf("Error in main_ast malloc\n");
	ptr = whole_list;
	while (ptr)
	{
		if (ft_strncmp(ptr->str, "|", 1) == 0)
		{
			ast_node->left = cmd_node_branch(whole_list);
			ast_node->right = ast (ast_node, ptr->next);
			return (ast_node);
		}
		ptr = ptr->next;
	}
	if (ptr == NULL)
		ast_node->right = cmd_node_branch(whole_list);
	return (ast_node);
}
