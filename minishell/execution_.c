/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoo <aoo@student.42singapore.sg>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 09:30:40 by aoo               #+#    #+#             */
/*   Updated: 2025/03/14 09:59:44 by aoo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	external(t_ast *l_node, int	*org_fd, t_core *core)
{
	pid_t	pid;
	int		status;

	(signal(SIGINT, SIG_IGN), signal(SIGQUIT, SIG_IGN));
	pid = fork();
	if (pid == -1)
		return (perror("fork operation failed!"), 1);
	if (pid == 0)
	{
		(close(org_fd[0]), close(org_fd[1]));
		(signal(SIGINT, SIG_DFL), signal(SIGQUIT, SIG_DFL));
		if (l_node->args)
		{
			exec_cmd(l_node->args, core);
		}
	}
	waitpid(pid, &status, 0);
	if (core->single_time)
		return (signal_print(status));
	return (signal_pipe_exit(status, core));
}

int	execution_cmd(t_ast *l_node, t_core *core, int *org_fd)
{
	char	**args;

	args = l_node->args;
	if (l_node->redirect && redirection(l_node->redirect) == -1)
		return (1);
	if (!args || !*args)
		return (0);
	if (!ft_strcmp(*args, "env"))
		return (env(core->envp));
	else if (!ft_strcmp(*args, "export"))
		return (export(args, core->envp, core->status));
	else if (!ft_strcmp(*args, "unset"))
		return (unset(args, &core->envp));
	else if (!ft_strcmp(*args, "echo"))
		return (echo_n(args));
	else if (!ft_strcmp(*args, "pwd"))
		return (pwd());
	else if (!ft_strcmp(*args, "cd"))
		return (cd(args, core->envp));
	else if (!ft_strcmp(*args, "exit"))
		return (ft_exit(args, org_fd, core));
	else
		return (external(l_node, org_fd, core));
}

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

pid_t	child_process_execution(t_ast *ast_node, t_core *core, int *pipe_fds,
	int *org_fd)
{
	if (!ast_node && !ast_node->left)
		return (core->status);
	(signal(SIGINT, SIG_IGN), signal(SIGQUIT, SIG_IGN));
	core->pid = fork();
	if (core->pid == -1)
		return (perror("minishell : fork failed"), 1);
	if (core->pid == 0)
		child_execute(ast_node, core, pipe_fds, org_fd);
	else
	{
		dup2(pipe_fds[0], STDIN_FILENO);
		(close(pipe_fds[1]), close(pipe_fds[0]));
	}
	return (core->pid);
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
		signal_print(signal_status(core->status));
	}
	reset_close_fd(org_fd, 1, 1);
	(signal(SIGINT, handle_sigint), signal(SIGQUIT, SIG_IGN));
	if (g_sig_interrupt)
		g_sig_interrupt = 0;
}
