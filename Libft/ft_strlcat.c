/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoo <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 15:29:19 by aoo               #+#    #+#             */
/*   Updated: 2024/05/19 15:30:27 by aoo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	s_len;
	size_t	d_len;
	size_t	t_len;
	int		i;

	s_len = ft_strlen((char *)src);
	d_len = ft_strlen(dst);
	t_len = s_len + d_len;
	if (size <= d_len)
		return (size + s_len);
	i = 0;
	while (src[i] && size - 1 > d_len)
		dst[d_len++] = src[i++];
	dst[d_len] = 0;
	return (t_len);
}
