/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 13:32:19 by aoo               #+#    #+#             */
/*   Updated: 2025/03/05 15:39:40 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	envp_arrsize(t_list *envp)
{
	int	i;

	i = 0;
	while (envp)
	{
		if (((t_envp *)envp->data)->value != NULL)
			i++;
		envp = envp->next;
	}
	return (i);
}

char	**envp_toarray(t_list *envp)
{
	t_envp	*envp_var;
	char	**envp_array;
	int		i;

	i = 0;
	envp_array = (char **)malloc(sizeof(char *) * (envp_arrsize(envp) + 1));
	while (envp)
	{
		envp_var = (t_envp *)envp->data;
		if (envp_var->value != NULL)
		{
			envp_array[i] = ft_strjoin(envp_var->key, "=", 0, 0);
			envp_array[i] = ft_strjoin(envp_array[i], envp_var->value, 1, 0);
			i++;
		}
		envp = envp->next;
	}
	return (envp_array[i] = NULL, envp_array);
}

t_list	*copy_envp(t_list *envp)
{
	t_list	*result;
	t_envp	*env_var;

	result = NULL;
	while (envp)
	{
		env_var = (t_envp *)malloc(sizeof(t_envp));
		env_var->key = ft_strdup(((t_envp *)envp->data)->key);
		env_var->value = ft_strdup(((t_envp *)envp->data)->value);
		ft_lstadd_back(&result, ft_lstnew((void *)env_var));
		envp = envp->next;
	}
	return (result);
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

void	export_noargs(t_list *envp)
{
	t_list	*copy;

	copy = copy_envp(envp);
	sort_envp(copy);
	ft_lstiter(copy, print_export);
}
