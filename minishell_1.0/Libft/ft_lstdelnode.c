/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelnode.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoo <aoo@student.42singapore.sg>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 21:23:19 by aoo               #+#    #+#             */
/*   Updated: 2025/01/27 21:41:25 by aoo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelnode(t_list **lst, void *data, \
		int (*match)(void *, void *), void (*del)(void *))
{
	t_list	*lst_pair[2];

	if (!lst || !*lst || !data || !match || !del)
		return ;
	lst_pair[0] = NULL;
	lst_pair[1] = *lst;
	while (lst_pair[1])
	{
		if (match(lst_pair[1]->data, data))
		{
			if (lst_pair[0])
				lst_pair[0]->next = lst_pair[1]->next;
			else
				*lst = lst_pair[1]->next;
			ft_lstdelone(lst_pair[1], del);
			return ;
		}
		lst_pair[0] = lst_pair[1];
		lst_pair[1] = lst_pair[1]->next;
	}
}
