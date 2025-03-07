/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtokr_c.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoo <aoo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 10:59:20 by aoo               #+#    #+#             */
/*   Updated: 2025/01/13 18:28:18 by aoo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_quote(char *q_chars, char c, int *in_quote)
{
	if (!q_chars)
		return (0);
	if (ft_strchr(q_chars, c))
	{
		if (!*in_quote)
			*in_quote = c;
		else if (*in_quote == c)
			*in_quote = !*in_quote;
	}
	return (*in_quote);
}

char	*ft_strtokr_c(char *str, const char *delim, \
		char *q_chars, char **saveptr)
{
	int		in_quote;
	char	*start;

	in_quote = 0;
	if (!str)
		str = *saveptr;
	while (*str && ft_strchr(delim, *str) && \
	!is_quote(q_chars, *str, &in_quote))
		str++;
	if (!*str)
		return (NULL);
	start = str;
	while (*str && (in_quote || !ft_strchr(delim, *str)))
		is_quote(q_chars, *str++, &in_quote);
	if (*str)
	{
		*str = '\0';
		*saveptr = str + 1;
	}
	else
		*saveptr = str;
	return (start);
}
