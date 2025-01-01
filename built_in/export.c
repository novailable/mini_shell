/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoo <aoo@student.42singapore.sg>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 21:18:45 by aoo               #+#    #+#             */
/*   Updated: 2025/01/01 13:50:57 by aoo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	print_env(void *data)
{
	t_envp	*env_var;

	env_var = (t_envp *)data;
	if (env_var)
		printf("%s=%s\'\n", env_var->key, env_var->value);
}

void	new_env(char *key_pair, char ***envp)
{
	int		i;
	char	**new_envp;

	i = 0;
	while ((*envp)[i])
		i++;
	new_envp = (char **)malloc(sizeof(char *) * (i + 2));
	if (!new_envp)
		return ;
	i = 0;
	while ((*envp)[i])
	{
		new_envp[i] = ft_strdup((*envp)[i]);
		i++;
	}
	new_envp[i] = ft_strdup(key_pair);
	new_envp[i + 1] = NULL;
	i = 0;
	while ((*envp)[i])
		free((*envp)[i++]);
	free(*envp);
	*envp = new_envp;
}

char	*find_env(char *key, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(key, envp[i], ft_strlen(key)) == 0)
			return (envp[i]);
		i++;
	}
	return (NULL);
}

char	*ft_getenv(char *key, char **envp)
{
	char	*env_var;

	env_var = find_env(key, envp);
	if (env_var)
		return (ft_strchr(env_var, '=') + 1);
	return (NULL);
}

void	update_env(char *key_pair, char **envp)
{
	char	*env_var;
	int		i;

	env_var = ft_getenv(key_pair, envp);
	if (env_var)
	{
		free(env_var);
		env_var = ft_strdup(key_pair);
	}
}

// export TEST=test A=$TEST B='$TEST' C="$TEST";
void	export(char **args, char	***envp)
{
	int		i;
	char	*key_pair;
	char	*save;
	
	i = 0;
	if (!args)
		while (*(envp[i]))
			printf("declare -x %s\n", *(envp[i++]));
	else
	{
		// while (args[i])
		// {
		// 	key_pair = ft_strdup(args[i]);
		// 	key = ft_strtokr_c(key_pair, "=", NULL, &save);
		// 	value = ft_str
		// 	if (find_env(ft_strtokr_c(key_pair, "=", NULL, &save), *envp))
				
		// 	i++;
		// }		
		// env(*envp);
		// printf("\n\n");
		new_env(args[0], envp);
	}
}