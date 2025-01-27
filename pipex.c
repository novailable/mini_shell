/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoo <aoo@student.42singapore.sg>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 20:40:00 by aoo               #+#    #+#             */
/*   Updated: 2025/01/27 20:29:38 by aoo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


// git@vogsphere.42singapore.sg:vogsphere/intra-uuid-6a11efd9-addf-4986-a46a-efcbe487b3a6-6135996-aoo
#include "pipex.h"

char	*get_p_path(char *cmd, char *envp_path)
{
	char	**paths;
	char	*s_path;
	char	*path;
	int		i;

	paths = ft_split((envp_path) + 5, ':');
	i = 0;
	while (paths[i])
	{
		s_path = ft_strjoin("/", cmd);
		path = ft_strjoin(paths[i], s_path);
		free(s_path);
		if (!access(path, F_OK | R_OK | X_OK))
			break ;
		free(path);
		path = NULL;
		i++;
	}
	i = 0;
	while (paths[i])
		free(paths[i++]);
	free(paths);
	if (!path)
		return (cmd);
	return (path);
}

int	exec_cmd(char *cmd, char **env)
{
	char	**argv;
	char	*path;
	int		exec_status;
	int		i;

	exec_status = -1;
	argv = ft_split(cmd, ' ');
	if (!argv)
		return (exec_status);
	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5))
		i++;
	if (ft_strncmp(argv[0], "./", 2))
		path = get_p_path(argv[0], env[i]);
	else
		path = argv[0];
	exec_status = execve(path, argv, env);
	if (path != argv[0])
		free(path);
	i = 0;
	while (argv[i])
		free(argv[i++]);
	free(argv);
	return (exec_status);
}

void	redirect(t_fds t_fds, int first)
{
	int	signal1;
	int	signal2;

	if (first)
	{
		signal1 = dup2(t_fds.in_fd, STDIN_FILENO);
		signal2 = dup2(t_fds.pipe_fd[1], STDOUT_FILENO);
	}
	else
	{
		signal1 = dup2(t_fds.pipe_fd[0], STDIN_FILENO);
		signal2 = dup2(t_fds.out_fd, STDOUT_FILENO);
	}
	close(t_fds.in_fd);
	close(t_fds.out_fd);
	close(t_fds.pipe_fd[0]);
	close(t_fds.pipe_fd[1]);
	if (signal1 == -1 || signal2 == -1)
		exit(1);
}

pid_t	fork_process(char *cmd, char **env, t_fds t_fds, int first)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("Fork operation failed!");
		exit(1);
	}
	if (pid == 0)
	{
		redirect(t_fds, first);
		if (exec_cmd(cmd, env) == -1)
		{
			perror("command not found ");
			if (errno == EACCES)
				exit(126);
			exit(127);
		}
		exit(0);
	}
	return (pid);
}

int	main(int argc, char **argv, char **env)
{
	int		status;
	t_fds	t_fds;
	pid_t	pid2;
	pid_t	pid1;

	status = 1;
	if (argc != 5)
		return (perror("Usage : ./pipex infile \"ls -l\" \"wc -l\" outfile"), 1);
	t_fds.in_fd = open(argv[1], O_RDONLY);
	if (t_fds.in_fd == -1)
		perror("Input file error!");
	t_fds.out_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (t_fds.out_fd == -1)
		perror("Output file error!");
	if (pipe(t_fds.pipe_fd) == -1)
		return (perror("Pipe operation failed!"), 1);
	pid1 = fork_process(argv[2], env, t_fds, 1);
	pid2 = fork_process(argv[3], env, t_fds, 0);
	close(t_fds.in_fd);
	close(t_fds.out_fd);
	close(t_fds.pipe_fd[0]);
	close(t_fds.pipe_fd[1]);
	waitpid(pid1, &status, 0);
	waitpid(pid2, &status, 0);
	return (WEXITSTATUS(status));
}
