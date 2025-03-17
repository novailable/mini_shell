/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoo <aoo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 16:31:50 by aoo               #+#    #+#             */
/*   Updated: 2025/03/15 19:31:49 by aoo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *big, const char *little)
{
	size_t		i;
	const char	*start;

	if (little && !*little)
		return ((char *)big);
	while (big && *big)
	{
		i = 0;
		start = big;
		while (little[i] && *big == little[i])
		{
			i++;
			big++;
		}
		if (little[i] == 0)
			return ((char *)start);
		big = start + 1;
	}
	return (NULL);
}
