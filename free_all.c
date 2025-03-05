/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:49:13 by nsan              #+#    #+#             */
/*   Updated: 2025/03/05 15:41:18 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_tokens *head)
{
	t_tokens	*temp;

	while (head)
	{
		temp = head;
		head = head->next;
		free(temp->str);
		free(temp);
	}
}

void	ret_free_envp(char *str, t_list *envp, t_tokens *tokens)
{
	printf("%s", str);
	if (tokens)
		free_tokens(tokens);
	if (envp)
		ft_lstclear(&envp, free_envp);
}

void	free_tokens_ast(t_tokens *tokens, t_ast *ast_node)
{
	free_tokens (tokens);
	free_ast (ast_node);
	free (ast_node);
}

void	free_envp(void *data)
{
	t_envp	*env_var;

	env_var = (t_envp *)data;
	free(env_var->key);
	free(env_var->value);
	free(env_var);
}
