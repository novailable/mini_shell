/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsan <nsan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:03:30 by aoo               #+#    #+#             */
/*   Updated: 2025/03/16 21:18:05 by nsan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*copy_envp(t_list *envp)
{
	t_list	*result;
	t_envp	*env_var;

	result = NULL;
	while (envp)
	{
		env_var = (t_envp *)malloc(sizeof(t_envp));
		if (!env_var)
			return (printf("copy envp malloc failed\n"), NULL);
		env_var->key = ft_strdup(((t_envp *)envp->data)->key);
		env_var->value = ft_strdup(((t_envp *)envp->data)->value);
		ft_lstadd_back(&result, ft_lstnew((void *)env_var));
		envp = envp->next;
	}
	return (result);
}

int	env_key_check(char *key, char *args)
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
	temp = args;
	if (!temp || !*temp)
		temp = key;
	return (print_err_msg("export : `", key, \
			"': not a valid identifier\n"), 1);
}

void	sort_envp(t_list *envp)
{
	int		swapped;
	void	*temp;
	t_list	*current;

	if (!envp)
		return ;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		current = envp;
		while (current && current->next)
		{
			if (ft_strcmp(((t_envp *)current->data)->key,
					((t_envp *)current->next->data)->key) > 0)
			{
				temp = current->data;
				current->data = current->next->data;
				current->next->data = temp;
				swapped = 1;
			}
			current = current->next;
		}
	}
}
