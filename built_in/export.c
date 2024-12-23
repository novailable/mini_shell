/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoo <aoo@student.42singapore.sg>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 21:18:45 by aoo               #+#    #+#             */
/*   Updated: 2024/12/23 09:15:31 by aoo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	new_env(char *key_pair, char ***envp)
{
	int		i;
	char	**new_envp;

	i = 0;
	while ((*envp)[i])
		i++;
	printf("i : %d\n", i);
	new_envp = (char **)malloc(sizeof(char *) * (i + 2));
	if (!new_envp)
		return ;
	i = 0;
	while ((*envp)[i])
	{
		new_envp[i] = strdup((*envp)[i]);
		i++;
	}
	new_envp[i] = strdup(key_pair);
	new_envp[i + 1] = NULL;
	*envp = new_envp;
}

char	*find_env(char *key, char **envp)
{
	while (*envp)
	{
		if (ft_strncmp(key, *envp, ft_strlen(key)) == 0)
			return (*envp);
		envp++;
	}
}

void	update_env(char **key_pair, char **envp)
{
	char	*env_entry;
	char	*new_entry;

	env_entry = find_env(key_pair[0], envp);
	if (env_entry)
	{
		new_entry = ft_strjoin(key_pair[0], key_pair[1]);
		if (!new_entry)
			return ;
		free(env_entry);
		env_entry = new_entry;
	}
}


void	export(char **args, char ***envp)
{
	int		i;
	char	**key_pair;

	i = 0;
	if (!args)
		while (envp[i])
			printf("declare -x %s\n", *(envp[i++]));
	else
	{
		while (args[i])
		{
			key_pair = ft_split(args[i], "=");
			if (find_env(key_pair[0], envp))
				update_env(key_pair, *envp);
			else
				new_env(args[i], envp);
			i++;
		}
	}
}
