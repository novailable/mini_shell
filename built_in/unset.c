/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoo <aoo@student.42singapore.sg>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 18:15:06 by aoo               #+#    #+#             */
/*   Updated: 2025/01/20 12:22:20 by aoo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	unset(char **args, t_list **envp)
{
	t_list	*prev_node;
	t_list	*curr_node;

	if (!args || !envp || !*envp)
		return ;
	while (*++args)
	{
		curr_node = *envp;
		prev_node = NULL;
		while (curr_node)
		{
			if (((t_envp *)curr_node->data)->key && \
			!ft_strcmp(((t_envp *)curr_node->data)->key, *args))
			{
				if (prev_node)
					prev_node->next = curr_node->next;
				else
					*envp = curr_node->next;
				ft_lstdelone(curr_node, free_envp);
				break ;
			}
			prev_node = curr_node;
			curr_node = curr_node->next;
		}
	}
}
