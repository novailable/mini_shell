/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoo <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:20:10 by aoo               #+#    #+#             */
/*   Updated: 2024/05/27 15:20:14 by aoo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*result;
	t_list	*n_node;
	t_list	*last;
	void	*item;

	result = NULL;
	while (lst)
	{
		item = f(lst->content);
		n_node = ft_lstnew(item);
		if (!n_node)
		{
			del(item);
			ft_lstclear(&result, del);
			return (NULL);
		}
		if (!result)
			result = n_node;
		else
			last->next = n_node;
		last = n_node;
		lst = lst->next;
	}
	return (result);
}
