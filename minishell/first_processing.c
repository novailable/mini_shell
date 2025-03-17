/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_processing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoo <aoo@student.42singapore.sg>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 19:33:28 by aoo               #+#    #+#             */
/*   Updated: 2025/03/17 13:57:00 by aoo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*quote_encoder(char *str)
{
	int		i;
	char	*result;

	result = NULL;
	i = 0;
	while (str && str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			result = ft_strcjoin(result, QUOTE_MARKER);
		result = ft_strcjoin(result, str[i++]);
	}
	return (result);
}

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
		*result = ft_strjoin(*result, quote_encoder(ft_getenv(start, core->envp)), 1, 1);
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
			result = ft_strjoin(result, "<<", 1, 0);
			while (*++str && ft_strchr(" \t", *++str))
				str++;
		}
		if (here_doc && ft_strchr(" \t", *str))
			here_doc = 0;
		if (!here_doc && *str == '$' && in_quote != '\'' && \
			!ft_strstr(result, "export"))
			str = replace_env(str, &result, core);
		else if (*str)
			result = ft_strcjoin(result, *str++);
	}
	return (result);
}
