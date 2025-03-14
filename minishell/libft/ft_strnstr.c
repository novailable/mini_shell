/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoo <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 18:55:52 by aoo               #+#    #+#             */
/*   Updated: 2024/05/19 18:56:04 by aoo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t		i;
	const char	*start;

	if (!*little)
		return ((char *)big);
	while (*big && len)
	{
		i = 0;
		start = big;
		while (little[i] && *big == little[i] && i < len)
		{
			if (little[i + 1] == 0 && (i + 1) <= len)
				return ((char *)start);
			i++;
			big++;
		}
		big = start + 1;
		len--;
	}
	return (NULL);
}
