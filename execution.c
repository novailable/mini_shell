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

int	external(char **args, t_list *envp)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		return (perror("fork operation failed!"), 1);
	if (pid == 0)
	{
		if (args)
		{
			if (exec_cmd(args, envp) == -1)
			{
				ft_putstr_fd(args[0], 2);
				perror("command not found ");
				if (errno == EACCES)
					exit (126);
				exit(127);
			}
			exit (0);
		}
	}
	return (waitpid(pid, &status, 0), WEXITSTATUS(status));
}

	/*
	int i;
	
	i = 0;
	while (envp_array[i])
		free(envp_array[i++]);
	free(envp_array);
	*/

int	execution(t_ast *node, t_list **envp)
{
	char	**args;

	args = node->args;
	if (node->redirect)
		redirection(node->redirect, *envp);
	if (!ft_strcmp(*args, "env"))
		return (env(*envp));
	else if (!ft_strcmp(*args, "export"))
		return (export(args, *envp));
	else if (!ft_strcmp(*args, "unset"))
		return (unset(args, envp));
	else
		return (external(args, *envp));
}

int	execute_ast(t_ast *ast_node, t_list *envp)
{
	pid_t	pid;
	int		pipe_fd[2];
	int		org_fd[2];
	int		status;

	status = 1;
	org_fd[0] = dup(STDIN_FILENO);
	org_fd[1] = dup(STDOUT_FILENO);
	if (ast_node->right)
	{
		pipe(pipe_fd);
		pid = fork();
		if (pid == -1)
			return (perror("fork operation failed!"), 1);
		if (pid == 0)
		{
			dup2(pipe_fd[1], STDOUT_FILENO);
			execution(ast_node->left, &envp);
			(close(pipe_fd[0]), close(pipe_fd[1]));
		}
		waitpid(pid, &status, 0);
		dup2(pipe_fd[0], STDIN_FILENO);
		(close(pipe_fd[0]), close(pipe_fd[1]));
		status = WEXITSTATUS(status);
		execute_ast(ast_node->right, envp);
	}
	else
	{
		status = execution(ast_node->left, &envp);
		dup2(STDIN_FILENO, org_fd[0]);
		dup2(STDOUT_FILENO, org_fd[1]);
		if (pipe_fd)
			(close(pipe_fd[0]), close(pipe_fd[1]));
		return (status);
	}
}

