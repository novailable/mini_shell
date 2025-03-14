/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_core.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoo <aoo@student.42singapore.sg>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 19:00:59 by nsan              #+#    #+#             */
/*   Updated: 2025/03/14 09:58:34 by aoo              ###   ########.fr       */
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
		else
			value = ft_strdup(value);
		// else if (!ft_strcmp(key, "SHELL"))
			// value = ft_strdup("minishell");
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
	core->history_path = ft_strjoin(ft_getenv("PWD", core->envp), \
									"/.minihistory", 0, 0);
	core->status = 0;
	core->single_time = 1;
	core->pid = -1;
	return (core);
}
