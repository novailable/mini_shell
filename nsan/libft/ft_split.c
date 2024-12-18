/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 17:53:02 by nsan              #+#    #+#             */
/*   Updated: 2024/06/03 09:02:29 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	word_count(const char *s, char c)
{
	int	count;
	int	flag;

	count = 0;
	flag = 0;
	while (*s)
	{
		if (*s != c && !flag)
		{
			flag = 1;
			count++;
		}
		else if (*s == c)
		{
			flag = 0;
		}
		s++;
	}
	return (count);
}

static char	*strn_dup(const char *s, size_t len)
{
	char	*word_dup;

	word_dup = (char *)malloc(len + 1);
	if (!word_dup)
		return (NULL);
	word_dup[len] = '\0';
	while (len--)
		word_dup[len] = s[len];
	return (word_dup);
}

static char	**make_split(char **dest, char const *s, char c)
{
	int		i;
	char	*start;

	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			start = (char *)s;
			while (*s && *s != c)
				s++;
			dest[i] = strn_dup(start, s - start);
			if (!dest[i])
			{
				while (i > 0)
					free(dest[--i]);
				return (NULL);
			}
			i++;
		}
		else
			s++;
	}
	dest[i] = NULL;
	return (dest);
}

char	**ft_split(char const *s, char c)
{
	char	**dest;

	if (!s)
		return (NULL);
	dest = (char **)malloc(sizeof(char *) * (word_count(s, c) + 1));
	if (!dest)
		return (NULL);
	if (!make_split(dest, s, c))
	{
		free(dest);
		return (NULL);
	}
	return (dest);
}
