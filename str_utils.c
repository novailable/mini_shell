/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 17:01:19 by nsan              #+#    #+#             */
/*   Updated: 2025/03/05 15:36:04 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quote_check(const char *input_str)
{
	int	flag;
	int	i;

	flag = 0;
	i = 0;
	while (input_str[i])
	{
		if (input_str[i] == '\"')
			return (1);
		i++;
	}
	return (0);
}

void	handle_newline(char *buf, int sz)
{
	int	i;

	i = -1;
	while (++i < sz)
	{
		if (buf[i] != '\n')
			write(1, &buf[i], 1);
		else
			write(1, "\n", 1);
	}
}

char	*ft_strcjoin(char *str, char c)
{
	char	*result;
	int		char_len;
	int		i;

	char_len = 2;
	if (c == '\0')
		char_len = 1;
	result = malloc(sizeof(char) * (ft_strlen(str) + char_len));
	i = 0;
	while (str && str[i])
	{
		result[i] = str[i];
		i++;
	}
	if (c)
		result[i++] = c;
	result[i] = '\0';
	if (str)
		free(str);
	return (result);
}

void	ft_strsncpy(char **dest, char **src, int n)
{
	int	i;

	i = 0;
	while (src[i] && i < n)
	{
		dest[i] = ft_strdup(src[i]);
		if (!dest[i])
			free_mem(dest, i);
		i++;
	}
}

int	is_in_quote(char *str)
{
	int	i;
	int	in_quote;

	i = 0;
	in_quote = 0;
	while (str[i])
	{
		is_quote("\'\"", str[i], &in_quote);
		i++;
	}
	return (in_quote);
}
