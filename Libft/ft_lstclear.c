/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoo <aoo@student.42singapore.sg>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:18:26 by aoo               #+#    #+#             */
/*   Updated: 2024/12/23 13:26:13 by aoo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*cur_lst;

	while (*lst && del)
	{
		cur_lst = (*lst)->next;
		del((*lst)->data);
		free(*lst);
		*lst = cur_lst;
	}
	*lst = NULL;
}
