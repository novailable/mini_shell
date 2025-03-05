/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memove.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoo <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:41:56 by aoo               #+#    #+#             */
/*   Updated: 2024/05/17 16:42:07 by aoo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*s;
	char	*d;

	if (dest == NULL && src == NULL)
		return (dest);
	s = (char *)src;
	d = (char *)dest;
	if (s < d && s + n > d)
		while (n--)
			d[n] = s[n];
	else
		while (n--)
			*d++ = *s++;
	return (dest);
}
