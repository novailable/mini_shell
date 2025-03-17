/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchrs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoo <aoo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 16:31:45 by aoo               #+#    #+#             */
/*   Updated: 2025/03/16 16:34:12 by aoo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchrs(char *str, char *delimeters)
{
	while (*str)
	{
		if (ft_strchr(delimeters, *str))
			return (str);
		str++;
	}
	return (NULL);
}
