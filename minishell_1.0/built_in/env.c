/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoo <aoo@student.42singapore.sg>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 21:18:55 by aoo               #+#    #+#             */
/*   Updated: 2025/01/27 11:52:39 by aoo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_env(void *data)
{
	t_envp	*env_var;

	env_var = (t_envp *)data;
	if (env_var->key && env_var->value)
		printf("%s=%s\n", env_var->key, env_var->value);
}

int	env(t_list *envp)
{
	return (ft_lstiter(envp, print_env), 0);
}
