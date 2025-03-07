/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_vali.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoo <aoo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 23:59:55 by aoo               #+#    #+#             */
/*   Updated: 2024/10/31 21:18:22 by aoo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	ft_atoi_vali(const char *nptr, int *result)
{
	long	i;
	int		sign;

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
	if ((i * sign) > INT_MAX || (i * sign) < INT_MIN)
		return (false);
	*result = i * sign;
	return (true);
}
