/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 12:51:10 by marvin            #+#    #+#             */
/*   Updated: 2025/01/23 12:51:10 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_ast(t_ast *ast_node)
{
	int i;
	t_ast   *node;
	i = 0;
	if (ast_node->left)
	{
		node = ast_node->left;
		printf("LEFT :\n\targs : ");
		while (node->args && node->args[i])
			printf("%s, ", node->args[i++]);
		printf("\n");
		i = 0;
		printf("\tredirect : ");
		while (node->redirect && node->redirect[i])
			printf("%s, ", node->redirect[i++]);
		printf("\n");
	}
	if(ast_node->right)
	{
		printf("RIGHT\n");
		print_ast(ast_node->right);
	}  
}


void	free_ast(t_ast *ast_node)
{
	t_ast   *node;
	int     i;

	if(ast_node->left)
	{
		node = ast_node->left;
		i = 0;
		if(node->args)
			free_strs(node->args);
		if(node->redirect)
			free_strs(node->redirect);
		free(node);
	}
	if(ast_node->right)
	{
		free_ast(ast_node->right);
		free(ast_node->right);
	}
}