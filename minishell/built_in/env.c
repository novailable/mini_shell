/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsan <nsan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 21:18:55 by aoo               #+#    #+#             */
/*   Updated: 2025/03/16 20:49:32 by nsan             ###   ########.fr       */
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

int	env(char **args, t_core *core)
{
	size_t	size;

	size = 0;
	while (args[size])
		size++;
	if (size > 1)
		return (print_err_msg(args[1], \
				": no such file or directory\n", NULL), 127);
	return (ft_lstiter(core->envp, print_env), 0);
}
