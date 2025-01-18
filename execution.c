#include "mini_shell.h"

char	*get_p_path(char *cmd, char *envp_path)
{
	char	**paths;
	char	*s_path;
	char	*path;
	int		i;

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
	while (paths[i])
		free(paths[i++]);
	free(paths);
	if (!path)
		return (cmd);
	return (path);
}


int	exec_cmd(char **args, t_list *envp)
{
	char	**envp_array;
	char	*path;
	int		exe_status;

	envp_array = envp_toarray(envp);
	path = get_p_path(args[0], ft_getenv("PATH", envp));
	exe_status = execve(path, args, envp_array);
	return (exe_status);
	/*
	int i;
	
	i = 0;
	while (envp_array[i])
		free(envp_array[i++]);
	free(envp_array);
	*/
}