#include "minishell.h"

char	*get_p_path(char *cmd, char *envp_path)
{
	char	**paths;
	char	*s_path;
	char	*path;
	int		i;

	if (!envp_path || !ft_strncmp(cmd, ".", 1))
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
	free_strs(paths);
	if (!path)
		return (cmd);
	return (path);
}

int	exec_cmd(char **args, t_core *core)
{
	char	**envp_array;
	char	*path;
	int		status;

	status = -1;
	envp_array = envp_toarray(core->envp);
	path = get_p_path(args[0], ft_getenv("PATH", core->envp));
	status = execve(path, args, envp_array);
	printf("%d\n", status);
	free_strs(envp_array);
	if (status == -1)
	{
		print_err_msg(args[0]);
		free(path);
		if (errno == EACCES)
			(perror(" "), exit(126));
		else if (errno == ENOENT)
			(ft_putstr_fd(": command not found\n", 2), exit(127));
		else
			(perror(" "), exit(EXIT_FAILURE));
	}


	// status = execve(path, args, envp_array);
	// if (status == -1)
	// 	perror(" leeee pal ");
	// if (ft_strcmp(path, *args))
	// 	free(path);
	return (status);
}

int	external(t_ast *l_node, int	*org_fd, t_core *core)
{
	pid_t	pid;
	int		status;

	stop_signal();
	pid = fork();
	if (pid == -1)
		return (perror("fork operation failed!"), 1);
	if (pid == 0)
	{
		(close(org_fd[0]), close(org_fd[1]));
		default_signal();
		if (l_node->args)
		{
			if (exec_cmd(l_node->args, core) == -1)
			{
				ft_putstr_fd(l_node->args[0], 2);
				free_core(core);
				if (errno == EACCES)
					exit (126);
				exit(127);
			}
			printf("ok\n");
			exit (0);
		}
	}
	waitpid(pid, &status, 0);
	// dprintf(2, "external : %d %d\n", status, wait_signal(status));
	return (signal_status(status));
}

int	execution(t_ast *l_node, t_core *core, int *org_fd)
{
	char	**args;

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
		return (env(core->envp));
	else if (!ft_strcmp(*args, "export"))
		return (export(args, core->envp, core->status));
	else if (!ft_strcmp(*args, "unset"))
		return (unset(args, &core->envp));
	else if (!ft_strcmp(*args, "echo"))
		return (echo_n(args, core->envp, core->status));
	else if (!ft_strcmp(*args, "pwd"))
		return (pwd());
	else if (!ft_strcmp(*args, "cd"))
		return (cd(args, core->envp));
	else if (!ft_strcmp(*args, "history"))
		return (history_output());
	else
		return (external(l_node, org_fd, core));
}

int execute_pipe(t_ast *ast_node, t_core *core, int *org_fd)
{
	pid_t pid;
	int pipe_fds[2];
	int exit_status;

	if (!ast_node && !ast_node->left)
		return (core->status);
	if (pipe(pipe_fds) == -1)
		return (perror("minishell : pipe failed"), 1);
	pid = fork();
	if (pid == -1)
		return (perror("minishell : fork failed"), 1);
	if (pid == 0)
	{
		default_signal();
		(close(org_fd[0]), close(org_fd[1]));
		close(pipe_fds[0]);
		if (ast_node->right)
			dup2(pipe_fds[1], STDOUT_FILENO);
		close(pipe_fds[1]);
		core->status = execution(ast_node->left, core, org_fd);
		free_core(core);
		exit(core->status);
	}
	// if (ast_node->right)
		dup2(pipe_fds[0], STDIN_FILENO);
	(close(pipe_fds[1]), close(pipe_fds[0]));
	if (ast_node->right)
	{
		exit_status = execute_pipe(ast_node->right, core, org_fd);
		waitpid(pid, &core->status, 0);
		signal_print(core->status);
	}
	else
	{
		waitpid(pid, &core->status, 0);
		exit_status = signal_status(core->status);
		signal_print(exit_status);
	}
	return (exit_status);
}

void	update_udscore_env(t_ast *l_node, t_core *core)
{
	char	*export_cmds[5];
	char	**args;
	char	*env_str;

	export_cmds[0] = "export";
	if (l_node->args && l_node->args[0])
	{
		args = l_node->args;
		while (args && *args)
			args++;
		env_str = ft_strjoin("_=", *(--args), 0, 0);
	}
	else
		env_str = ft_strjoin("_=", "\0", 0, 0);
	export_cmds[1] = env_str;
	export_cmds[2] = NULL;
	export(export_cmds, core->envp, core->status);
	free(env_str);
}

int	execute_ast(t_core *core)
{
	int		org_fd[2];
	t_ast	*ast_node;

	stop_signal();
	ast_node = core->ast;
	org_fd[0] = dup(STDIN_FILENO);
	org_fd[1] = dup(STDOUT_FILENO);
	if (core->ast && core->ast->right)
		core->status = execute_pipe(ast_node, core, org_fd);
	else if (ast_node && ast_node->left)
	{
		update_udscore_env(ast_node->left, core);
		core->status = execution(ast_node->left, core, org_fd);
		signal_print(core->status);
	}
	dup2(org_fd[0], STDIN_FILENO);
	dup2(org_fd[1], STDOUT_FILENO);
	(close(org_fd[0]), close(org_fd[1]));
	// dprintf(2, "exe ast g sig : %d\n", g_sig_interrupt);
	set_signal();
	if (g_sig_interrupt)
		g_sig_interrupt = 0;
	return (core->status);
}
