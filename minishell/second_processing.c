/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second_processing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoo <aoo@student.42singapore.sg>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 13:56:29 by aoo               #+#    #+#             */
/*   Updated: 2025/03/17 13:57:16 by aoo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quote_decoder(char **str, char **result)
{
	char	*save;

	save = *str;
	if (save && *save == QUOTE_MARKER && ft_strchr("\'\"", *(save + 1)))
	{
		*result = ft_strcjoin(*result, *++save);
		*str = save;
		return (1);
	}
	return (0);
}

char	*handle_dq(char *str, char **result)
{
	str++;
	while (*str && *str != '\"')
	{
		if (!quote_decoder(&str, result))
			*result = ft_strcjoin(*result, *str++);
	}
	*result = ft_strcjoin(*result, '\0');
	str++;
	return (str);
}

char	*handle_quotes(char *str)
{
	char	*result;

	result = NULL;
	while (str && *str)
	{
		if (quote_decoder(&str, &result) && *str++)
			continue ;
		if (*str == '\'')
		{
			++str;
			while (*str && *str != '\'')
				if (!quote_decoder(&str, &result))
					result = ft_strcjoin(result, *str++);
			result = ft_strcjoin(result, '\0');
			str++;
		}
		else if (*str == '\"')
			str = handle_dq(str, &result);
		else if (*str)
			result = ft_strcjoin(result, *str++);
	}
	return (result);
}
