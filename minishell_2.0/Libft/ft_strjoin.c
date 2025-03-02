/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoo <aoo@student.42singapore.sg>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 21:31:29 by aoo               #+#    #+#             */
/*   Updated: 2025/01/01 10:13:58 by aoo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2, int fs1, int fs2)
{
	char	*result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	// if (!s1 || !s2)
	// 	return (NULL);
	result = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (result == NULL)
		return (NULL);
	while (s1 && s1[i])
		result[i++] = s1[j++];
	j = 0;
	while (s2 && s2[j])
		result[i++] = s2[j++];
	result[i] = 0;
	if (s1 && fs1)
		free(s1);
	if (s2 && fs2)
		free(s2);
	return (result);
}
