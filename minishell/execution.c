/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoo <aoo@student.42singapore.sg>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:51:10 by aoo               #+#    #+#             */
/*   Updated: 2025/03/14 09:53:56 by aoo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_execute(t_ast *ast_node, t_core *core, int *pipe_fds, int *org_fd)
{
	int	exit_status;

	reset_close_fd(org_fd, 0, 1);
	if (ast_node->right)
		dup2(pipe_fds[1], STDOUT_FILENO);
	(close(pipe_fds[0]), close(pipe_fds[1]));
	exit_status = execution_cmd(ast_node->left, core, org_fd);
	free_core(core);
	exit(exit_status);
}

int	signal_print_check(t_ast *ast_node)
{
	return (ast_node->left->args && ast_node->left->args[0] && \
			ft_strcmp(ast_node->left->args[0], "exit"));
}

pid_t	child_process_execution(t_ast *ast_node, t_core *core, int *pipe_fds,
	int *org_fd)
{
	pid_t	pid;

	if (!ast_node && !ast_node->left)
		return (core->status);
	(signal(SIGINT, SIG_IGN), signal(SIGQUIT, SIG_IGN));
	pid = fork();
	if (pid == -1)
		return (perror("minishell : fork failed"), 1);
	if (pid == 0)
		child_execute(ast_node, core, pipe_fds, org_fd);
	else
	{
		dup2(pipe_fds[0], STDIN_FILENO);
		(close(pipe_fds[1]), close(pipe_fds[0]));
	}
	return (pid);
}

int	execute_pipe(t_ast *ast_node, t_core *core, int *org_fd)
{
	pid_t	pid;
	int		pipe_fds[2];
	int		exit_status;

	if (!ast_node && !ast_node->left)
		return (core->status);
	if (pipe(pipe_fds) == -1)
		return (perror("minishell : pipe failed"), 1);
	pid = child_process_execution(ast_node, core, pipe_fds, org_fd);
	if (ast_node->right)
	{
		exit_status = execute_pipe(ast_node->right, core, org_fd);
		waitpid(pid, &core->status, 0);
		exit_status = signal_print(core->status);
	}
	else
	{
		waitpid(pid, &core->status, 0);
		exit_status = signal_status(core->status);
		signal_print(exit_status);
	}
	return (exit_status);
}

void	execute_ast(t_core *core)
{
	int		org_fd[2];
	t_ast	*ast_node;

	ast_node = core->ast;
	org_fd[0] = dup(STDIN_FILENO);
	org_fd[1] = dup(STDOUT_FILENO);
	if (core->ast && core->ast->right)
	{
		core->single_time = 0;
		core->status = execute_pipe(ast_node, core, org_fd);
	}
	else if (ast_node && ast_node->left)
	{
		core->single_time = 1;
		update_udscore_env(ast_node->left, core);
		core->status = execution_cmd(ast_node->left, core, org_fd);
		signal_print(core->status);
	}
	reset_close_fd(org_fd, 1, 1);
	(signal(SIGINT, handle_sigint), signal(SIGQUIT, SIG_IGN));
	if (g_sig_interrupt)
		g_sig_interrupt = 0;
}
