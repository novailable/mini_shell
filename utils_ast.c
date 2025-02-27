/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsan <nsan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 02:28:23 by nsan              #+#    #+#             */
/*   Updated: 2025/02/11 19:24:14 by nsan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ast(t_ast *ast_node, t_tokens *whole_list)
{
	t_tokens	*ptr;

	ast_node->left = malloc(sizeof(t_ast));
	ptr = whole_list;
	ptr = args_redirection_list (ast_node->left, ptr);
	if (ptr && ft_strcmp(ptr->str, "|") == 0)
	{
		ast_node->right = malloc(sizeof(t_ast));
		ast (ast_node->right, ptr->next);
	}
	else
		ast_node->right = NULL;
}
