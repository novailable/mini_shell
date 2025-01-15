/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoo <aoo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 21:18:45 by aoo               #+#    #+#             */
/*   Updated: 2025/01/14 02:16:29 by aoo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	new_env(char *key, char *value, t_list *envp)
{
	t_envp	*env_var;

	env_var = (t_envp *)malloc(sizeof(t_envp));
	if (!env_var)
		return ;
	env_var->key = ft_strdup(key);
	env_var->value = ft_strdup(value);
	ft_lstadd_back(&envp, ft_lstnew((void *)env_var));
}

t_list	*find_env(char *key, t_list *envp)
{
	t_envp	*env_var;

	while (envp)
	{
		env_var = (t_envp *)envp->data;
		if (env_var && env_var->key && \
			!ft_strcmp(env_var->key, key))
			return (envp);
		envp = envp->next;
	}
	return (NULL);
}

char	*ft_getenv(char *key, t_list *envp)
{
	t_list	*get_envp;

	get_envp = find_env(key, envp);
	if (get_envp)
		return (((t_envp *)get_envp->data)->value);
	return (NULL);
}

void	update_env(char *value, t_list *envp)
{
	t_envp	*env_var;

	env_var = (t_envp *)envp->data;
	if (value)
	{
		if (env_var->value)
			free(env_var->value);
		env_var->value = ft_strdup(value);
	}
}

void	get_keypair(char *arg, char *result[2], t_list *envp)
{
	char	*value;

	value = ft_strchr(arg, '=');
	if (value)
	{
		result[0] = ft_strndup(arg, value - arg);
		if (ft_strcmp(value, "=") == 0)
			result[1] = ft_strdup("");
		else
			result[1] = first_processing(++value, envp);
	}
	else
	{
		result[0] = ft_strdup(arg);
		result[1] = NULL;
	}
}

int	export(char **args, t_list *envp)
{
	int		i;
	char	*keypair[2];
	char	*save;
	int		status;

	i = 0;
	status = 0;
	save = NULL;
	if (!args[1])
		return (export_noargs(envp), status);
	while (args[++i])
	{
		get_keypair(args[i], keypair, envp);
		if (env_key_check(keypair[0]))
		{
			if (find_env(keypair[0], envp))
				update_env(keypair[1], find_env(keypair[0], envp));
			else
				new_env(keypair[0], keypair[1], envp);
		}
		else
			status = (printf("%s\n", args[i]) * 0) + 1;
		(free(keypair[0]), free(keypair[1]));
	}
	return (status);
}
