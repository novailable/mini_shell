<<<<<<< HEAD
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
	if (l_node && l_node->redirect)
		if (redirection(l_node) == -1)
			return (1);
	if(g_sig_interruption)
	{
		g_sig_interruption = 0;
		return (130);
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

// Execute the pipeline with prepared heredocs
int execute_pipeline(t_ast *ast_node, t_list *envp, int status)
{
    if (!ast_node || !ast_node->right)
        return status;
    
    int pipe_fds[2];
    pid_t pid;
    
    if (pipe(pipe_fds) == -1)
        return (perror("minishell : pipe failed"), 1);
    
    pid = fork();
    if (pid == -1)
        return (perror("minishell : fork failed"), 1);
    if (pid == 0)
    {
        // Child process executes the left command
        dup2(pipe_fds[1], STDOUT_FILENO);
        (close(pipe_fds[0]), close(pipe_fds[1]));
        
        // Apply redirections including prepared heredocs
        if (apply_redirections(ast_node->left) == -1)
            exit(1);
        
        exit(execution(ast_node->left, envp, status));
    }
    
    // Parent process continues
    dup2(pipe_fds[0], STDIN_FILENO);
    (close(pipe_fds[0]), close(pipe_fds[1]));
    
    // If right side is another pipe, recurse
    if (ast_node->right->right)
    {
        return execute_pipeline(ast_node->right, envp, status);
    }
    else
    {
        // Execute final command in pipeline
        pid_t last_pid = fork();
        if (last_pid == -1)
            return (perror("minishell : fork failed"), 1);
            
        if (last_pid == 0)
        {
            // Apply redirections including prepared heredocs
            if (apply_redirections(ast_node->right->left) == -1)
                exit(1);
                
            exit(execution(ast_node->right->left, envp, status));
        }
        
        // Wait for all processes
        int pipe_status;
        waitpid(pid, NULL, 0);
        waitpid(last_pid, &pipe_status, 0);
        
        if (WIFEXITED(pipe_status))
            return WEXITSTATUS(pipe_status);
        return pipe_status;
    }
}

// Prepare all heredocs in a pipeline before executing any commands
int prepare_heredocs_for_pipeline(t_ast *ast_node, t_list *envp, int status)
{
    if (!ast_node)
        return 1;
    
    // Process current node
    if (ast_node->left && ast_node->left->redirect)
    {
		
        // Store heredoc FDs in a global structure or attach them to the AST node
        if (!prepare_heredocs_for_node(ast_node->left, envp, status))
            return 0;
    }
    
    // Process right branch (if it exists)
    if (ast_node->right)
        return prepare_heredocs_for_pipeline(ast_node->right, envp, status);
    
    return 1;
}


// New function to specifically handle pipelines with heredocs
int handle_pipeline(t_ast *ast_node, t_list *envp, int status)
{
    // Store all heredoc file descriptors for each command in the pipeline
    // This will be done before any command execution
    if (!prepare_heredocs_for_pipeline(ast_node, envp, status))
        return 1;
    
    // Now execute the pipeline with the heredocs already prepared
    return execute_pipeline(ast_node, envp, status);
}

int execute_ast(t_ast *ast_node, t_list *envp, int status)
{
    int org_fd[2];
    
    org_fd[0] = dup(STDIN_FILENO);
    org_fd[1] = dup(STDOUT_FILENO);
    
    if (ast_node && ast_node->right)
    {
        // This is a piped command
        status = handle_pipeline(ast_node, envp, status);
    }
    else if (ast_node && ast_node->left)
    {
        // This is a single command
		prepare_heredocs_for_node(ast_node->left, envp, status);
        status = execution(ast_node->left, envp, status);
    }
    
    dup2(org_fd[0], STDIN_FILENO);
    dup2(org_fd[1], STDOUT_FILENO);
    (close(org_fd[0]), close(org_fd[1]));
    
    return (status);
}
=======
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
	if (l_node && l_node->redirect)
		if (redirection(l_node) == -1)
			return (1);
	if(g_sig_interruption)
	{
		g_sig_interruption = 0;
		return (130);
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

// Execute the pipeline with prepared heredocs
int execute_pipeline(t_ast *ast_node, t_list *envp, int status)
{
    if (!ast_node || !ast_node->right)
        return status;
    
    int pipe_fds[2];
    pid_t pid;
    
    if (pipe(pipe_fds) == -1)
        return (perror("minishell : pipe failed"), 1);
    
    pid = fork();
    if (pid == -1)
        return (perror("minishell : fork failed"), 1);
    if (pid == 0)
    {
        // Child process executes the left command
        dup2(pipe_fds[1], STDOUT_FILENO);
        (close(pipe_fds[0]), close(pipe_fds[1]));
        
        // Apply redirections including prepared heredocs
        if (apply_redirections(ast_node->left) == -1)
            exit(1);
        
        exit(execution(ast_node->left, envp, status));
    }
    
    // Parent process continues
    dup2(pipe_fds[0], STDIN_FILENO);
    (close(pipe_fds[0]), close(pipe_fds[1]));
    
    // If right side is another pipe, recurse
    if (ast_node->right->right)
    {
        return execute_pipeline(ast_node->right, envp, status);
    }
    else
    {
        // Execute final command in pipeline
        pid_t last_pid = fork();
        if (last_pid == -1)
            return (perror("minishell : fork failed"), 1);
            
        if (last_pid == 0)
        {
            // Apply redirections including prepared heredocs
            if (apply_redirections(ast_node->right->left) == -1)
                exit(1);
                
            exit(execution(ast_node->right->left, envp, status));
        }
        
        // Wait for all processes
        int pipe_status;
        waitpid(pid, NULL, 0);
        waitpid(last_pid, &pipe_status, 0);
        
        if (WIFEXITED(pipe_status))
            return WEXITSTATUS(pipe_status);
        return pipe_status;
    }
}

// Prepare all heredocs in a pipeline before executing any commands
int prepare_heredocs_for_pipeline(t_ast *ast_node, t_list *envp, int status)
{
    if (!ast_node)
        return 1;
    
    // Process current node
    if (ast_node->left && ast_node->left->redirect)
    {
		
        // Store heredoc FDs in a global structure or attach them to the AST node
        if (!prepare_heredocs_for_node(ast_node->left, envp, status))
            return 0;
    }
    
    // Process right branch (if it exists)
    if (ast_node->right)
        return prepare_heredocs_for_pipeline(ast_node->right, envp, status);
    
    return 1;
}


// New function to specifically handle pipelines with heredocs
int handle_pipeline(t_ast *ast_node, t_list *envp, int status)
{
    // Store all heredoc file descriptors for each command in the pipeline
    // This will be done before any command execution
    if (!prepare_heredocs_for_pipeline(ast_node, envp, status))
        return 1;
    
    // Now execute the pipeline with the heredocs already prepared
    return execute_pipeline(ast_node, envp, status);
}

int execute_ast(t_ast *ast_node, t_list *envp, int status)
{
    int org_fd[2];
    
    org_fd[0] = dup(STDIN_FILENO);
    org_fd[1] = dup(STDOUT_FILENO);
    
    if (ast_node && ast_node->right)
    {
        // This is a piped command
        status = handle_pipeline(ast_node, envp, status);
    }
    else if (ast_node && ast_node->left)
    {
        // This is a single command
		prepare_heredocs_for_node(ast_node->left, envp, status);
        status = execution(ast_node->left, envp, status);
    }
    
    dup2(org_fd[0], STDIN_FILENO);
    dup2(org_fd[1], STDOUT_FILENO);
    (close(org_fd[0]), close(org_fd[1]));
    
    return (status);
}
>>>>>>> 4cdeb0f6219f9fcf8d9941a671c90a0876c7291f
