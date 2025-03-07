/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 15:21:05 by marvin            #+#    #+#             */
/*   Updated: 2025/03/05 15:21:05 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*init_env_empty(t_list *envp)
{
	char	*pwd;

	envp = NULL;
	pwd = getcwd(NULL, 0);
	new_env("PWD", pwd, &envp);
	new_env("SHLVL", "1", &envp);
	new_env("_", "./minishell", &envp);
	free(pwd);
	return (envp);
}

t_list	*init_envp(char **envpath)
{
	t_list	*envp;
	char	*key;
	char	*value;

	envp = NULL;
	if (!envpath || !*envpath)
		return (init_env_empty(envp));
	while (*envpath)
	{
		key = ft_strndup(*envpath, ft_strchr(*envpath, '=') - *envpath);
		value = ft_strchr(*envpath, '=') + 1;
		if (!ft_strcmp(key, "SHLVL"))
			value = ft_itoa(atoi(value) + 1);
		else
			value = ft_strdup(value);
		new_env(key, value, &envp);
		(free(key), free(value));
		envpath++;
	}
	return (envp);
}

int	env_key_check(char *key)
{
	char	*temp;

	temp = key;
	if (temp && *temp && !ft_isdigit(*temp))
	{
		while (*temp && (ft_isalnum(*temp) || *temp == '_'))
		{
			temp++;
			if (*temp == '\0')
				return (0);
		}
	}
	return (printf("export : not a valid identifier : %s\n", key), 1);
}
