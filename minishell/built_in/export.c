/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsan <nsan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 21:18:45 by aoo               #+#    #+#             */
/*   Updated: 2025/03/16 21:18:12 by nsan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	new_env(char *key, char *value, t_list **envp)
{
	t_envp	*env_var;

	env_var = (t_envp *)malloc(sizeof(t_envp));
	if (!env_var)
	{
		printf("new env malloc failed\n");
		return ;
	}
	env_var->key = ft_strdup(key);
	env_var->value = ft_strdup(value);
	ft_lstadd_back(envp, ft_lstnew((void *)env_var));
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

void	export_noargs(t_list *envp)
{
	t_list	*copy;

	copy = copy_envp(envp);
	sort_envp(copy);
	ft_lstiter(copy, print_export);
	ft_lstclear(&copy, free_envp);
}

void	print_export(void *data)
{
	t_envp	*env_var;

	env_var = (t_envp *)data;
	if (ft_strcmp(env_var->key, "_"))
	{
		printf("deaclare -x %s", env_var->key);
		if (env_var->value)
			printf("=\"%s\"", env_var->value);
		printf("\n");
	}
}

int	export(char **args, t_core *core)
{
	int		i;
	char	*keypair[2];
	int		status;

	i = 0;
	status = 0;
	if (!args[1])
		export_noargs(core->envp);
	while (args[++i])
	{
		get_keypair(args[i], keypair, core);
		if (!env_key_check(keypair[0], args[i]))
		{
			if (find_env(keypair[0], core->envp))
				update_env(keypair[1], find_env(keypair[0], core->envp));
			else
				new_env(keypair[0], keypair[1], &core->envp);
		}
		else
			status = 1;
		(free(keypair[0]), free(keypair[1]));
	}
	return (status);
}
