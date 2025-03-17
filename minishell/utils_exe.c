/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoo <aoo@student.42singapore.sg>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 19:02:13 by nsan              #+#    #+#             */
/*   Updated: 2025/03/17 13:48:59 by aoo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_cmd(char **args, char *path, t_core *core)
{
	char	**envp_array;

	envp_array = envp_toarray(core->envp);
	if (execve(path, args, envp_array) == -1)
	{
		if (path)
			free(path);
		free_strs(envp_array);
		if (errno == ENOENT)
			(print_err_msg(args[0], ": command not found\n", NULL), \
			free_core(core), exit(127));
		else if (errno == EACCES)
			(print_err_msg(args[0], NULL, NULL), \
			perror(" "), free_core(core), exit(126));
		(perror(" "), free_core(core), exit(1));
	}
}

int	external(t_ast *l_node, int	*org_fd, t_core *core)
{
	pid_t	pid;
	int		status;
	char	*path;
	int		path_status;

	(signal(SIGINT, SIG_IGN), signal(SIGQUIT, SIG_IGN));
	path_status = get_p_path(l_node->args[0], \
				ft_getenv("PATH", core->envp), &path);
	if (path_status != 0)
		return (path_status);
	pid = fork();
	if (pid == -1)
		return (perror("fork operation failed!"), 1);
	if (pid == 0)
	{
		(close(org_fd[0]), close(org_fd[1]));
		(signal(SIGINT, SIG_DFL), signal(SIGQUIT, SIG_DFL));
		if (l_node->args)
			exec_cmd(l_node->args, path, core);
	}
	waitpid(pid, &status, 0);
	free(path);
	return (signal_status(status));
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
		return (env(args, core));
	else if (!ft_strcmp(*args, "export"))
		return (export(args, core));
	else if (!ft_strcmp(*args, "unset"))
		return (unset(args, &core->envp));
	else if (!ft_strcmp(*args, "echo"))
		return (echo_n(args));
	else if (!ft_strcmp(*args, "pwd"))
		return (pwd());
	else if (!ft_strcmp(*args, "cd"))
		return (cd(args, core));
	else if (!ft_strcmp(*args, "exit"))
		return (ft_exit(args, org_fd, core));
	else
		return (external(l_node, org_fd, core));
}

void	update_udscore_env(t_ast *l_node, t_core *core)
{
	char	*export_cmds[3];
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
		env_str = ft_strdup("_=");
	export_cmds[1] = env_str;
	export_cmds[2] = NULL;
	export(export_cmds, core);
	free(env_str);
}
