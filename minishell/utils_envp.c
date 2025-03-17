/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_envp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoo <aoo@student.42singapore.sg>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 19:01:33 by nsan              #+#    #+#             */
/*   Updated: 2025/03/17 13:46:17 by aoo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	get_keypair(char *arg, char *result[2], t_core *core)
{
	char	*value;
	char	*temp;

	temp = handle_env(arg, core);
	value = ft_strchr(temp, '=');
	if (value)
	{
		result[0] = ft_strndup(temp, value - temp);
		if (ft_strcmp(value, "=") == 0)
			result[1] = ft_strdup("");
		else
			result[1] = ft_strdup(++value);
	}
	else
	{
		result[0] = ft_strdup(temp);
		result[1] = NULL;
	}
	free(temp);
}
