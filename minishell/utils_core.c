/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_core.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsan <nsan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 19:00:59 by nsan              #+#    #+#             */
/*   Updated: 2025/03/16 22:47:58 by nsan             ###   ########.fr       */
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
			value = ft_itoa(ft_atoi(value) + 1); 
		else if (!ft_strcmp(key, "SHELL"))
			value = ft_strdup("minishell");
		else
			value = ft_strdup(value);
		new_env(key, value, &envp);
		(free(key), free(value));
		envpath++;
	}
	return (envp);
}

t_core	*init_core(char **envpath)
{
	t_core	*core;

	core = (t_core *)malloc(sizeof(t_core));
	if (!core)
		return (NULL);
	core->envp = init_envp(envpath);
	core->tokens = NULL;
	core->ast = NULL;
	core->input = NULL;
	core->status = 0;
	core->single_time = 1;
	ft_memset((void *)core, 0, sizeof(core));
	return (core);
}
