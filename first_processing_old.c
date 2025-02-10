/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_processing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoo <aoo@student.42singapore.sg>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 18:03:02 by aoo               #+#    #+#             */
/*   Updated: 2025/02/03 09:12:45 by aoo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_esc(char *str, char **result, int in_quote)
{
	str++;
	if (*str == '\n')
		str += 2;
	else if (ft_strchr("\\\'\" $", *str))
		*result = ft_strcjoin(*result, *str++);
	else if (in_quote)
		*result = ft_strcjoin(*result, '\\');
	else
		*result = ft_strcjoin(*result, *str++);
	return (str);
}

char	*handle_env(char *str, char **result, t_list *envp, int status)
{
	char	*start;
	char	*s_value;

	start = ++str;
	if (*start == '?')
	{
		s_value = ft_itoa(status);
		*result = ft_strjoin(*result, s_value, 1, 1);
		return (str);
	}
	while (*str && (ft_isalnum(*str) || *str == '_'))
		str++;
	start = ft_strndup(start, str - start);
	if (start && *start)
		*result = ft_strjoin(*result, ft_getenv(start, envp), 1, 0);
	else
		*result = ft_strcjoin(*result, '$');
	if (start)
		free(start);
	return (str);
}

char	*handle_sq(char *str, char **result)
{
	++str;
	while (*str && *str != '\'')
	{
		*result = ft_strcjoin(*result, *str++);
	}
	*result = ft_strcjoin(*result, '\0');
	str++;
	return (str);
}

char	*handle_dq(char *str, char **result, t_list *envp, int status)
{
	str++;
	while (*str && *str != '\"')
	{
		if (*str == '\\')
			str = handle_esc(str, result, 1);
		else if (*str == '$')
			str = handle_env(str, result, envp, status);
		else
			*result = ft_strcjoin(*result, *str++);
	}
	*result = ft_strcjoin(*result, '\0');
	str++;
	return (str);
}

char	*first_processing(char *str, t_list *envp, int status)
{
	char	*result;

	result = NULL;
	while (str && *str)
	{
		if (*str == '\\')
			str = handle_esc(str, &result, 0);
		else if (*str == '$')
			str = handle_env(str, &result, envp, status);
		else if (*str == '\'')
			str = handle_sq(str, &result);
		else if (*str == '\"')
			str = handle_dq(str, &result, envp, status);
		else
			result = ft_strcjoin(result, *str++);
	}
	return (result);
}
