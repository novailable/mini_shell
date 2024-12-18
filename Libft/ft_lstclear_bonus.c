/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoo <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:18:26 by aoo               #+#    #+#             */
/*   Updated: 2024/05/27 15:18:41 by aoo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*cur_lst;

	while (*lst && del)
	{
		cur_lst = (*lst)->next;
		del((*lst)->content);
		free(*lst);
		*lst = cur_lst;
	}
	*lst = NULL;
}
