/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoo <aoo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:49:13 by nsan              #+#    #+#             */
/*   Updated: 2025/03/10 17:49:44 by aoo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_ast(t_ast **ast)
{
	t_ast	*node;

	if (!ast || !*ast)
		return ;
	node = *ast;
	if (node->left)
	{
		if (node->left->args)
			free_strs(node->left->args);
		if (node->left->redirect)
			free_strs(node->left->redirect);
		free(node->left);
		node->left = NULL;
	}
	if (node->right)
	{
		free_ast(&node->right);
		node->right = NULL;
	}
	free(node);
	*ast = NULL;
}

void	free_tokens(t_tokens **head)
{
	t_tokens	*temp;

	while (*head)
	{
		temp = *head;
		*head = (*head)->next;
		free(temp->str);
		free(temp);
		temp = NULL;
	}
}

void	free_envp(void *data)
{
	t_envp	*env_var;

	env_var = (t_envp *)data;
	free(env_var->key);
	free(env_var->value);
	free(env_var);
}

void	reset_close_fd(int *org_fd, int reset, int closee)
{
	if (reset)
	{
		dup2(org_fd[0], STDIN_FILENO);
		dup2(org_fd[1], STDOUT_FILENO);
	}
	if (closee)
	{
		close(org_fd[0]);
		close(org_fd[1]);
	}
}

void	free_core(t_core *core)
{
	if (!core)
		return ;
	if (core->tokens)
		free_tokens(&core->tokens);
	if (core->ast)
		free_ast(&core->ast);
	if (core->envp)
		ft_lstclear(&core->envp, free_envp);
	if (core->input && *core->input)
	{
		free(core->input);
		core->input = NULL;
	}
	if (core->history_path && *core->history_path)
	{
		free(core->history_path);
		core->history_path = NULL;
	}
	free(core);
	rl_clear_history();
}
