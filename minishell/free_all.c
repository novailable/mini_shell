/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsan <nsan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:49:13 by nsan              #+#    #+#             */
/*   Updated: 2025/03/16 21:46:54 by nsan             ###   ########.fr       */
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

void	free_tokens(t_tokens **tokens)
{
	t_tokens	*temp;

	while (*tokens)
	{
		temp = (*tokens)->next;
		if ((*tokens)->str)
			free((*tokens)->str);
		free(*tokens);
		*tokens = temp;
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
	if (core->input)
		free_str(&core->input);
	free(core);
	rl_clear_history();
}
