/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 17:53:59 by nsan              #+#    #+#             */
/*   Updated: 2024/12/12 19:53:18 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*sr1;
	unsigned char	*sr2;

	i = 0;
	sr1 = (unsigned char *)s1;
	sr2 = (unsigned char *)s2;
	if (!n)
		return (0);
	while (sr1[i] == sr2[i] && i < n - 1 && sr1[i])
		i++;
	return (sr1[i] - sr2[i]);
}

