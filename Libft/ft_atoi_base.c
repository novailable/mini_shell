/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoo <aoo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 16:05:21 by aoo               #+#    #+#             */
/*   Updated: 2024/10/31 21:18:56 by aoo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	find_value(char c, char *base)
{
	int	value;

	value = 0;
	while (base[value])
	{
		if (base[value] == c)
			return (value);
		value++;
	}
	return (-1);
}

int	check_power(char *base)
{
	int	power;
	int	ptr;

	ptr = 0;
	power = 0;
	if (base[0] == 0 || base[1] == 0)
		return (0);
	while (base[power])
	{
		ptr = power;
		while (base[ptr++])
		{
			if (base[ptr] == base[power])
				return (0);
		}
		if (base[power] == '+' || base[power] == '-' || base[power] == '*' || \
			base[power] == '/' || base[power] == '%' || base[power] == 127 || \
			base[power] < 33)
			return (0);
		power++;
	}
	return (power);
}

bool	ft_atoi_base(char *str, char *base, int *value)
{
	int	power;
	int	sign;
	int	i;

	power = check_power(base);
	sign = 1;
	i = 0;
	if (!power)
		return (0);
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	while (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str)
	{
		if (find_value(*str, base) < 0)
			return (*value = 0, false);
		i = i * power + find_value(*str, base);
		str++;
	}
	return (*value = i * sign, true);
}
