/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoo <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 21:14:06 by aoo               #+#    #+#             */
/*   Updated: 2024/05/22 21:14:55 by aoo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*result;
	size_t	i;
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		len = 0;
	else if (start + len > s_len)
		len = s_len - start;
	result = (char *)malloc(len + 1);
	if (!result)
		return (NULL);
	i = 0;
	if (start > s_len)
	{
		result[0] = 0;
		return (result);
	}
	while (s[start] && i < len)
		result[i++] = s[start++];
	result[i] = 0;
	return (result);
}
