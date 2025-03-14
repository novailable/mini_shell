/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exe_new.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoo <aoo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:38:48 by aoo               #+#    #+#             */
/*   Updated: 2025/03/13 19:54:35 by aoo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_path(char *cmd, char *envp_path, char **path)
{
	char	**e_paths;
	int		i;

	if (!ft_strcmp(cmd, "."))
		return (print_err_msg(cmd, "filename argument required\n", NULL), 2);
	i = 0;
	e_paths = ft_split(envp_path, ":");
	while (e_paths[i])
	{
		*path = ft_strjoin(e_paths[i], ft_strjoin("/", cmd, 0, 0), 0, 1);
		if (!access(*path, F_OK | R_OK))
			break ;
		free(*path);
		*path = NULL;
		i++;
	}
	free_strs(e_paths);
	return (0);
}

int	get_p_path(char *cmd, char *envp_path, char **path)
{
	char		**paths;
	struct stat	st;
	
	if (!cmd || !*cmd)
		return (*path = ft_strdup(cmd), 0);
	if (!envp_path || ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK | R_OK ))
		{
			print_err_msg(cmd, "No such file or directory\n", NULL);
			return (*path = NULL, 127);
		}
		else if (stat(cmd, &st) == 0 && S_ISDIR(st.st_mode))
		{
			print_err_msg(cmd, ": is a directory\n", NULL);
			return (*path = NULL, 126);
		}
		return (*path = ft_strdup(cmd), 0);
	}
	return (find_path(cmd, envp_path, path));
}

void	exec_cmd(char **args, t_core *core)
{
	char	*path;
	int		path_status;
	char	**envp_array;

	path_status = get_p_path(args[0], ft_getenv("PATH", core->envp), &path);
	if (path_status != 0)
		(free_core(core), exit(path_status));
	envp_array = envp_toarray(core->envp);
	if (execve(path, args, envp_array) == -1)
	{
		if (path)
			free(path);
		free_strs(envp_array);
		if (errno == ENOENT)
			(print_err_msg(args[0], ": command not found\n", NULL), 
			free_core(core), exit(127));
		else if (errno == EACCES)
			(print_err_msg(args[0], NULL, NULL), \
			perror(" "), free_code(core), exit(126));
		(perror(" "), free_core(core), exit(1));
	}
}
