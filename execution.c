#include "minishell.h"

char	*get_p_path(char *cmd, char *envp_path)
{
	char	**paths;
	char	*s_path;
	char	*path;
	int		i;

	if (!envp_path)
		return (cmd);
	paths = ft_split((envp_path), ":");
	i = 0;
	while (paths[i])
	{
		s_path = ft_strjoin("/", cmd, 0, 0);
		path = ft_strjoin(paths[i], s_path, 0, 1);
		if (!access(path, F_OK | R_OK | X_OK))
			break ;
		free(path);
		path = NULL;
		i++;
	}
	i = 0;
	free_strs(paths);
	if (!path)
		return (cmd);
	return (path);
}

int	exec_cmd(char **args, t_list *envp)
{
	char	**envp_array;
	char	*path;
	int		status;

	status = -1;
	envp_array = envp_toarray(envp);
	path = get_p_path(args[0], ft_getenv("PATH", envp));
	status = execve(path, args, envp_array);
	if (ft_strcmp(path, *args))
		free(path);
	free_strs(envp_array);
	return (status);
}

int	external(t_ast *l_node, t_list *envp)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		return (perror("fork operation failed!"), 1);
	if (pid == 0)
	{
		if (l_node->args)
		{
			if (exec_cmd(l_node->args, envp) == -1)
			{
				ft_putstr_fd(l_node->args[0], 2);
				perror(" ");
				if (errno == EACCES)
					exit (126);
				exit(127);
			}
			exit (0);
		}
	}
	
	return (waitpid(pid, &status, 0), WEXITSTATUS(status));
}

int	execution(t_ast *l_node, t_list *envp, int status)
{
	char	**args;

	args = NULL;
	args = l_node->args;
	if (l_node->redirect)
	{
		if (redirection(l_node->redirect, envp, status) == -1)
			return (1);
	}
	if(g_sig_interruption)
	{
		g_sig_interruption = 0;
		return (0);
	}
	if (!args || !*args)
		return (0);
	if (!ft_strcmp(*args, "env"))
		return (env(envp));
	else if (!ft_strcmp(*args, "export"))
		return (export(args, envp, status));
	else if (!ft_strcmp(*args, "unset"))
		return (unset(args, &envp));
	else if (!ft_strcmp(*args, "echo"))
		return (echo_n(args, envp, status));
	else if (!ft_strcmp(*args, "pwd"))
		return (pwd());
	else if (!ft_strcmp(*args, "cd"))
		return (cd(args, envp));
	else if (!ft_strcmp(*args, "history"))
		return (history_output());
	else
		return (external(l_node, envp));
}

int	execute_right(t_ast *ast_node, t_list *envp, int status)
{
	pid_t	pid;
	int		pipe_fds[2];
	// sig_t org_signals[2];

	if (ast_node && ast_node->right)
	{
		if (pipe(pipe_fds) == -1)
			return (perror("minishell : pipe failed"), 1);
		// org_signals[0] = signal(SIGINT, handle_sigint_process);
		// org_signals[1] = signal(SIGQUIT, handle_sigquit_process);
		pid = fork();
		if (pid == -1)
			return (perror("minishell : fork failed"), 1);
		if (pid == 0)
		{
			dup2(pipe_fds[1], STDOUT_FILENO);
			(close(pipe_fds[0]), close(pipe_fds[1]));
			// signal(SIGINT, SIG_DFL);
			// signal(SIGQUIT, SIG_DFL);
			exit(execution(ast_node->left, envp, status));
			// exit(e_status);
		}
		dup2(pipe_fds[0], STDIN_FILENO);
		(close(pipe_fds[1]), close(pipe_fds[0]));
		execute_right(ast_node->right, envp, status);
		waitpid(pid, &status, 0);
		// signal(SIGINT, org_signals[0]);
		// signal(SIGQUIT, org_signals[1]);
		return (status);
	}
	else if (ast_node && ast_node->left)
	{
		pid = fork();
		if (pid == -1)
			return (perror("minishell : fork failed"), 1);
		if (pid == 0)
			exit(execution(ast_node->left, envp, status));
		return (pid);
	}
}

int	execute_ast(t_ast *ast_node, t_list *envp, int status)
{
	int	org_fd[2];
	int	last_pid;
	
    org_fd[0] = dup(STDIN_FILENO);
    org_fd[1] = dup(STDOUT_FILENO);
	if (ast_node && ast_node->right)
	{
		status = execute_right(ast_node, envp, status);
	}
	else if (ast_node && ast_node->left)
		status = execution(ast_node->left, envp, status);
    dup2(org_fd[0], STDIN_FILENO);
    dup2(org_fd[1], STDOUT_FILENO);
    (close(org_fd[0]), close(org_fd[1]));
	return (status);
}

// int	execute_ast(t_ast *ast_node, t_list *envp, int status)
// {
// 	int org_fds[2];

// 	org_fds[0] = dup(STDIN_FILENO);
// 	org_fds[1] = dup(STDOUT_FILENO);
// 	// printf("%d , %d\n", org_fds[0], org_fds[1]);
// 	status = execution(ast_node->left, envp, status);
// 	dup2(org_fds[0], STDIN_FILENO);
// 	dup2(org_fds[1], STDOUT_FILENO);
// 	// printf("%d %d\n", STDIN_FILENO, STDOUT_FILENO);
// 	// printf("%d %d\n", org_fds[0], org_fds[1]);
// 	close (org_fds[0]);
// 	close (org_fds[1]);
// 	return (status);
// }

// int	execute_ast(t_ast *ast_node, t_list *envp, int status)
// {
// 	pid_t	pid;
// 	int		pipe_fds[2];
// 	int		org_fd[2];
// 	int		last_pid = -1;

// 	// Save original stdin/stdout
// 	org_fd[0] = dup(STDIN_FILENO);
// 	org_fd[1] = dup(STDOUT_FILENO);

// 	if (ast_node && ast_node->right)
// 	{
// 		if (pipe(pipe_fds) == -1)
// 			return (perror("minishell: pipe failed"), 1);

// 		pid = fork();
// 		if (pid == -1)
// 			return (perror("minishell: fork failed"), 1);

// 		if (pid == 0) // Child process (left command)
// 		{
// 			dup2(pipe_fds[1], STDOUT_FILENO);
// 			close(pipe_fds[0]); // Close unused read end
// 			close(pipe_fds[1]);
// 			exit(execution(ast_node->left, envp, status));
// 		}

// 		close(pipe_fds[1]); // Parent closes write end
// 		dup2(pipe_fds[0], STDIN_FILENO); // Set input for next process
// 		close(pipe_fds[0]);

// 		// Continue with right part of AST (next command in pipeline)
// 		last_pid = execute_ast(ast_node->right, envp, status);
// 	}
// 	else if (ast_node && ast_node->left)
// 	{
// 		pid = fork();
// 		if (pid == 0)
// 			exit(execution(ast_node->left, envp, status));
// 		last_pid = pid;
// 	}

// 	// Restore original stdin/stdout after pipeline execution
// 	dup2(org_fd[0], STDIN_FILENO);
// 	dup2(org_fd[1], STDOUT_FILENO);
// 	close(org_fd[0]);
// 	close(org_fd[1]);

// 	// Parent waits for all child processes after execution
// 	if (last_pid != -1)
// 	{
// 		int wstatus;
// 		while (waitpid(-1, &wstatus, 0) > 0)
// 			;
// 		return (WEXITSTATUS(wstatus));
// 	}
// 	return status;
// }

// int	execute_ast(t_ast *ast_node, t_list *envp, int status)
// {
// 	pid_t	pid;
// 	int		pipe_fds[2];
// 	int		org_fd[2];

// 	org_fd[0] = dup(STDIN_FILENO);
// 	org_fd[1] = dup(STDOUT_FILENO);
// 	if (ast_node && ast_node->right)
// 	{
// 		if (pipe(pipe_fds) == -1)
// 			return (perror("minishell : pipe failed"), 1);
// 		pid = fork();
// 		if (pid == -1)
// 			return (perror("minishell : fork failed"), 1);
// 		if (pid == 0)
// 		{
// 			dup2(pipe_fds[1], STDOUT_FILENO);
// 			(close (pipe_fds[0]), close (pipe_fds[1]));
// 			exit(execution(ast_node->left, envp, status));
// 		}
// 		close(pipe_fds[1]);
// 		dup2(pipe_fds[0], STDIN_FILENO);
// 		close(pipe_fds[0]);
// 		execute_ast(ast_node->right, envp, status);
// 		waitpid(-1, NULL, 0);
// 	}
// 	else if (ast_node && ast_node->left)
// 		status = execution(ast_node->left, envp, status);
// 	dup2(org_fd[0], STDIN_FILENO);
// 	dup2(org_fd[1], STDOUT_FILENO);
// 	return (close(org_fd[0]), close(org_fd[1]), status);
// }
