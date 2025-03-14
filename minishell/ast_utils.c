/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsan <nsan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:28:50 by nsan              #+#    #+#             */
/*   Updated: 2025/02/11 19:28:50 by nsan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_ast(t_ast *ast_node)
{
	int		i;
	t_ast	*node;

	i = 0;
	if (ast_node == NULL)
		printf("NULL\n");
	if (ast_node && ast_node->left)
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
	if (ast_node->right)
	{
		printf("RIGHT\n");
		print_ast(ast_node->right);
	}
}
