/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoo <aoo@student.42singapore.sg>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 13:35:49 by aoo               #+#    #+#             */
/*   Updated: 2024/12/30 09:45:04 by aoo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	is_quote(char *q_chars, char c, int *in_quote)
{
	if (ft_strchr(q_chars, c))
	{
		if (!*in_quote)
			*in_quote = c;
		else if (*in_quote == c)
			*in_quote = !*in_quote;
	}
	return (*in_quote);
}

// int	word_count(char *str, char *d_chars, char *q_chars)
// {
// 	int	count;
// 	int	in_word;
// 	int	in_quote;

// 	in_word = 0;
// 	in_quote = 0;
// 	count = 0;
// 	while (*str)
// 	{
// 		if (is_quote(q_chars, *str, &in_quote))
// 		{
// 			str++;
// 			str = ft_strchr(str, in_quote) + 1;
// 			count++;
// 			in_quote = 0;
// 		}
// 		if (!ft_strchr(d_chars, *str) && !in_word && !in_quote)
// 		{
// 			in_word = 1;
// 			count++;
// 		}
// 		else if (ft_strchr(d_chars, *str) || in_quote)
// 			in_word = 0;
// 		str++;
// 		if(in_quote && !*str)
// 			return (0);
// 		// is_quote(q_chars, *str, &in_quote);
// 		// if (!ft_strchr(d_chars, *str) && !in_word && !in_quote)
// 		// {
// 		// 	in_word = 1;
// 		// 	count++;
// 		// }
// 		// else if (ft_strchr(d_chars, *str) || in_quote)
// 		// 	in_word = 0;
// 		// str++;
// 		// if (in_quote && !*str)
// 		// 	return (0);
// 	}
// 	return (count);
// }

int	word_count(char *str, char *d_chars, char *q_chars)
{
	int	count;
	int	in_quote;

	in_quote = 0;
	count = 0;
	while (*str)               
	{
		if (!ft_strchr(d_chars, *str))
		{
			count++;
			while (*str && (!ft_strchr(d_chars, *str) || \
			is_quote(q_chars, *str, &in_quote)))
				str++;
		}
		else
			str++;
		if (!*str && in_quote)
			return (0);
	}
	return (count);
}

static int	ft_splitndup_2(char **r, const char *src, int len, int i)
{
	char	*result;
	int		j;

	j = 0;
	result = (char *)malloc((len + 1) * sizeof(char));
	if (!result)
	{
		while (i >= 0)
			free(r[i--]);
		free(r);
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

char	*make_splitting(char *str, char *d_chars, char *q_chars, char **result)
{
	char	*start;
	int		in_quote;
	int		i;

	i = 0;
	while (result[i])
		i++;
	in_quote = 0;
	if (is_quote(q_chars, *str, &in_quote))
	{
		start = ++str;
		str = ft_strchr(str, in_quote);
		ft_splitndup_2(result, start, str - start, i++);
		in_quote = 0;
		str++;
	}
	else if (!ft_strchr(d_chars, *str))
	{
		start = str;
		while (*str && !ft_strchr(d_chars, *str) && !ft_strchr(q_chars, *str))
			str++;
		ft_splitndup_2(result, start, str - start, i++);
	}
	else
		str++;
	return (str);
}

char	**ft_split_2(char *str, char *d_chars, char *q_chars)
{
	char		**result;
	int			w_count;
	int			i;
	int			in_quote;
	char		*start;

	if (!str)
		return (NULL);
	w_count = word_count(str, d_chars, q_chars);
	if (w_count == 0)
		return (NULL);	
	result = (char **)malloc((w_count + 1) * sizeof(char *));
	if (!result)
		return (perror("malloc failed"), NULL);
	i = 0;
	in_quote = 0;
	while (i < w_count)
		result[i++] = NULL;
	while (*str)
	{
		if (!ft_strchr(d_chars, *str))
		{
			start = str;
			while (*str && (!ft_strchr(d_chars, *str) || \
					is_quote(q_chars, *str, &in_quote)))
				str++;
			result[i] = ft_strndup(start, str - start);
			if (!result[i])
			{
				while (i-- > 0)
					free(result[i]);
				return (free(result), NULL);
			}
			i++;
		}
		else
			str++;
	}
	result[i] = NULL;
	return (result);
}
