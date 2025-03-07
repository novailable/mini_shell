/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoo <aoo@student.42singapore.sg>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 14:45:48 by aoo               #+#    #+#             */
/*   Updated: 2025/01/20 11:32:22 by aoo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	is_delimiter(char c, const char *delimiters)
{
	while (*delimiters)
		if (c == *delimiters++)
			return (1);
	return (0);
}

int	count_word(char const *s, const char *delimiters)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (!is_delimiter(*s, delimiters) && in_word == 0)
		{
			in_word = 1;
			count++;
		}
		else if (is_delimiter(*s, delimiters))
			in_word = 0;
		s++;
	}
	return (count);
}

void	free_mem(char **result, int i)
{
	while (i >= 0)
		free(result[i--]);
	free(result);
}

static int	ft_splitndup(char **r, const char *src, int len, int i)
{
	char	*result;
	int		j;

	j = 0;
	result = (char *)malloc((len + 1) * sizeof(char));
	if (!result)
	{
		free_mem(r, i);
		return (0);
	}
	while (j < len)
	{
		result[j] = src[j];
		j++;
	}
	result[j] = 0;
	r[i] = result;
	return (1);
}

char	**ft_split(char const *s, char *delimiters)
{
	char		**result;
	const char	*start;
	int			i;

	i = 0;
	if (!s)
		return (NULL);
	result = (char **)malloc((count_word(s, delimiters) + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	while (*s)
	{
		if (!is_delimiter(*s, delimiters))
		{
			start = s;
			while (*s && !is_delimiter(*s, delimiters))
				s++;
			if (!ft_splitndup(result, start, s - start, i++))
				return (NULL);
		}
		else
			s++;
	}
	result[i] = NULL;
	return (result);
}
