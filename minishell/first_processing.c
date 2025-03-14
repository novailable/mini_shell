/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_processing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoo <aoo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 19:33:28 by aoo               #+#    #+#             */
/*   Updated: 2025/03/12 16:12:21 by aoo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*replace_env(char *str, char **result, t_core *core)
{
	char	*start;
	char	*s_value;

	start = ++str;
	if (*start == '0')
		return (*result = ft_strjoin(*result, "minishell", 1, 0), (++str));
	if (*start == '?')
	{
		s_value = ft_itoa(core->status);
		*result = ft_strjoin(*result, s_value, 1, 1);
		return (++str);
	}
	if (ft_isdigit(*str))
		return (str + 1);
	while (*str && (ft_isalnum(*str) || *str == '_'))
		str++;
	start = ft_strndup(start, str - start);
	if (start && *start)
		*result = ft_strjoin(*result, ft_getenv(start, core->envp), 1, 0);
	else
		*result = ft_strcjoin(*result, '$');
	if (start)
		free(start);
	return (str);
}

char	*handle_env(char *str, t_core *core)
{
	char	*result;
	int		in_quote;
	int		here_doc;

	in_quote = 0;
	result = NULL;
	here_doc = 0;
	while (str && *str)
	{
		if (!is_quote("\'\"", *str, &in_quote) && !ft_strncmp("<<", str, 2))
		{
			here_doc = 1;
			result = ft_strcjoin(result, *str++);
			result = ft_strcjoin(result, *str++);
			while (*str && ft_strchr(" \t", *str))
				str++;
		}
		if (here_doc && ft_strchr(" \t", *str))
			here_doc = 0;
		if (!here_doc && *str == '$' && in_quote != '\'')
			str = replace_env(str, &result, core);
		else if (*str)
			result = ft_strcjoin(result, *str++);
	}
	return (result);
}

char	*handle_esc(char *str, char **result, int in_quote)
{
	str++;
	if (*str == '\n')
		str += 2;
	else if (ft_strchr("\'", *str) && !in_quote)
		*result = ft_strcjoin(*result, *str++);
	else if (ft_strchr("\\\" $", *str))
		*result = ft_strcjoin(*result, *str++);
	else if (in_quote)
		*result = ft_strcjoin(*result, '\\');
	else
		*result = ft_strcjoin(*result, *str++);
	return (str);
}

char	*handle_dq(char *str, char **result)
{
	str++;
	while (*str && *str != '\"')
		*result = ft_strcjoin(*result, *str++);
	*result = ft_strcjoin(*result, '\0');
	str++;
	return (str);
}

char	*handle_quotes(char *str)
{
	char	*result;

	result = NULL;
	while (*str)
	{
		if (*str == '\'')
		{
			++str;
			while (*str && *str != '\'')
				result = ft_strcjoin(result, *str++);
			result = ft_strcjoin(result, '\0');
			str++;
		}
		else if (*str == '\"')
			str = handle_dq(str, &result);
		else
			result = ft_strcjoin(result, *str++);
	}
	return (result);
}
