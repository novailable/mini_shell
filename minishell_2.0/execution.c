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

int	external(t_ast *l_node, int	*org_fd, t_list *envp)
{
	pid_t	pid;
	int		status;

	stop_signal();
	pid = fork();
	if (pid == -1)
		return (perror("fork operation failed!"), 1);
	if (pid == 0)
	{
		default_signal();
		(close(org_fd[0]), close(org_fd[1]));
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
	waitpid(pid, &status, 0);

	return (wait_signal_status(status));
}

int	execution(t_ast *l_node, int *org_fd, t_list *envp, int status)
{
	char	**args;

	args = NULL;
	args = l_node->args;
	if (l_node->redirect)
		if (redirection(l_node->redirect) == -1)
			return (1);
	// if(g_sig_interruption)
	// {
	// 	g_sig_interruption = 0;
	// 	return (130);
	// }
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
		return (external(l_node, org_fd, envp));
}
int execute_pipe(t_ast *ast_node, int *org_fd, t_list *envp, int status)
{
	pid_t pid;
	int pipe_fds[2];
	int exit_status;

	if (!ast_node && !ast_node->left)
		return (status);
	if (pipe(pipe_fds) == -1)
		return (perror("minishell : pipe failed"), 1);
	pid = fork();
	if (pid == -1)
		return (perror("minishell : fork failed"), 1);
	if (pid == 0)
	{
		default_signal();
		(close(org_fd[0]), close(org_fd[1]));
		if (ast_node->right)
			dup2(pipe_fds[1], STDOUT_FILENO);
		(close(pipe_fds[1]), close(pipe_fds[0]));
		exit(execution(ast_node->left, org_fd, envp, status));
	}
	if (ast_node->right)
		dup2(pipe_fds[0], STDIN_FILENO);
	(close(pipe_fds[1]), close(pipe_fds[0]));
	if (ast_node->right)
		exit_status = execute_pipe(ast_node->right, org_fd, envp, status);
	else
	{
		waitpid(pid, &status, 0);
		exit_status = status;
	}
	waitpid(pid, &status, 0);
	if (!ast_node->right)
		return(exit_status);
	return (wait_signal_status(exit_status));
}

int	execute_ast(t_ast *ast_node, t_list *envp, int status)
{
	int	org_fd[2];

	stop_signal();
	org_fd[0] = dup(STDIN_FILENO);
	org_fd[1] = dup(STDOUT_FILENO);
	if (ast_node && ast_node->right)
	{
		status = execute_pipe(ast_node, org_fd, envp, status);
	}
	else if (ast_node && ast_node->left)
		status = execution(ast_node->left, org_fd, envp, status);
	dup2(org_fd[0], STDIN_FILENO);
	dup2(org_fd[1], STDOUT_FILENO);
	(close(org_fd[0]), close(org_fd[1]));
	set_signal();
	return (status);
}