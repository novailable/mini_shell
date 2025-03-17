/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoo <aoo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 02:28:23 by nsan              #+#    #+#             */
/*   Updated: 2025/03/16 16:59:45 by aoo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_ast(t_ast *ast_node, t_tokens *whole_list)
{
	t_tokens	*ptr;

	ast_node->left = malloc(sizeof(t_ast));
	if (!ast_node->left)
	{
		printf("ast_node->left failed\n");
		return ;
	}
	ptr = whole_list;
	ptr = args_redirection_list (ast_node->left, ptr);
	if (ptr && ft_strcmp(ptr->str, "|") == 0)
	{
		ast_node->right = malloc(sizeof(t_ast));
		if (!ast_node->right)
		{
			printf("ast_node->right failed\n");
			return ;
		}
		create_ast(ast_node->right, ptr->next);
	}
	else
		ast_node->right = NULL;
}

int	init_ast(t_core *core)
{
	core->ast = (t_ast *)malloc(sizeof(t_ast));
	if (!core->ast)
		return (0);
	create_ast(core->ast, core->tokens);
	free_tokens(&core->tokens);
	return (1);
}
