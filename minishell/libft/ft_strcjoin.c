/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoo <aoo@student.42singapore.sg>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 20:30:34 by aoo               #+#    #+#             */
/*   Updated: 2025/03/08 20:30:37 by aoo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcjoin(char *str, char c)
{
	char	*result;
	int		char_len;
	int		i;

	char_len = 2;
	if (c == '\0')
		char_len = 1;
	result = malloc(sizeof(char) * (ft_strlen(str) + char_len));
	i = 0;
	while (str && str[i])
	{
		result[i] = str[i];
		i++;
	}
	if (c)
		result[i++] = c;
	result[i] = '\0';
	if (str)
		free(str);
	return (result);
}
