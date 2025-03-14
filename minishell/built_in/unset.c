/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoo <aoo@student.42singapore.sg>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 18:15:06 by aoo               #+#    #+#             */
/*   Updated: 2025/03/10 17:22:13 by aoo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_keymatch(void *dest_data, void *src_data)
{
	char	*d_key;

	d_key = ((t_envp *)dest_data)->key;
	if (d_key && !ft_strcmp(d_key, (char *)src_data))
		return (1);
	return (0);
}

int	unset(char **args, t_list **envp)
{
	int		status;

	status = 0;
	if (!args || !envp || !*envp)
		return (1);
	while (*++args)
	{
		if (!env_key_check(*args, NULL))
			ft_lstdelnode(envp, *args, is_keymatch, free_envp);
		else
			status = 1;
	}
	return (status);
}
