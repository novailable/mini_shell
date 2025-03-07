/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll_vali.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoo <aoo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 18:07:11 by aoo               #+#    #+#             */
/*   Updated: 2025/03/06 20:02:01 by aoo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	ft_atoll_vali(const char *nptr, long long *result)
{
	long long int	i;
	int		        sign;

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
	while (*nptr)
	{
		if (*nptr >= '0' && *nptr <= '9')
			i = i * 10 + (*nptr - '0');
		else
			return (false);
		nptr++;
	}
	if ((i * sign) > LLONG_MAX || (i * sign) < LLONG_MAX)
		return (false);
	*result = i * sign;
	return (true);
}
