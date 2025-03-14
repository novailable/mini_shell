/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll_vali.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoo <aoo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 18:07:11 by aoo               #+#    #+#             */
/*   Updated: 2025/03/13 14:56:46 by aoo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	ft_atoll_vali(const char *nptr, long long *result)
{
	long long	i;
	int			sign;

	i = 0;
	sign = 1;
	while (*nptr == ' ' || (*nptr >= '\t' && *nptr <= '\r'))
		nptr++;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		if (i > LLONG_MAX / 10 || (i == LLONG_MAX / 10 && \
			(*nptr - '0') > LLONG_MAX % 10 + (sign == -1)))
			return (false);
		i = i * 10 + (*nptr - '0');
		nptr++;
	}
	if (*nptr != '\0')
		return (false);
	*result = i * sign;
	return (true);
}
