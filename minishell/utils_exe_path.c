/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exe_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoo <aoo@student.42singapore.sg>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 19:01:58 by nsan              #+#    #+#             */
/*   Updated: 2025/03/17 10:17:40 by aoo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	envp_arrsize(t_list *envp)
{
	int	i;

	i = 0;
	while (envp)
	{
		if (((t_envp *)envp->data)->value != NULL)
			i++;
		envp = envp->next;
	}
	return (i);
}

char	**envp_toarray(t_list *envp)
{
	t_envp	*envp_var;
	char	**envp_array;
	int		i;

	i = 0;
	envp_array = (char **)malloc(sizeof(char *) * (envp_arrsize(envp) + 1));
	if (!envp_array)
		return (printf("env to array malloc failed\n"), NULL);
	while (envp)
	{
		envp_var = (t_envp *)envp->data;
		if (envp_var->value != NULL && ft_strcmp(envp_var->key, "_"))
		{
			envp_array[i] = ft_strjoin(envp_var->key, "=", 0, 0);
			envp_array[i] = ft_strjoin(envp_array[i], envp_var->value, 1, 0);
			i++;
		}
		envp = envp->next;
	}
	return (envp_array[i] = NULL, envp_array);
}

int	find_path(char *cmd, char *envp_path, char **path)
{
	char	**e_paths;
	int		i;

	if (!ft_strcmp(cmd, "."))
		return (print_err_msg(cmd, ": filename argument required\n", NULL), 2);
	if (!ft_strcmp(cmd, ".."))
		return (print_err_msg(cmd, ": command not found\n", NULL), 127);
	i = 0;
	e_paths = ft_split(envp_path, ":");
	while (e_paths[i])
	{
		*path = ft_strjoin(e_paths[i], ft_strjoin("/", cmd, 0, 0), 0, 1);
		if (!access(*path, F_OK))
			break ;
		free(*path);
		*path = NULL;
		i++;
	}
	free_strs(e_paths);
	if (*path == NULL)
		return (print_err_msg(cmd, ": command not found\n", NULL), 127);
	return (0);
}

int	get_p_path(char *cmd, char *envp_path, char **path)
{
	struct stat	st;

	if (!cmd || !*cmd)
		return (*path = ft_strdup(cmd), 0);
	if (!envp_path || ft_strchr(cmd, '/'))
	{
		if (stat(cmd, &st) == -1)
		{
			if (errno == EACCES)
			{
				print_err_msg(cmd, ": Permission denied\n", NULL);
				return (*path = NULL, 126);
			}		
			print_err_msg(cmd, ": No such file or directory\n", NULL);
			return (*path = NULL, 127);
		}
		if (stat(cmd, &st) == 0 && S_ISDIR(st.st_mode))
		{
			print_err_msg(cmd, ": is a directory\n", NULL);
			return (*path = NULL, 126);
		}
		return (*path = ft_strdup(cmd), 0);
	}
	return (find_path(cmd, envp_path, path));
}
