/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_processing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: nsan <nsan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 19:33:28 by aoo               #+#    #+#             */
/*   Updated: 2025/03/03 17:36:31 by nsan             ###   ########.fr       */
=======
/*   By: aoo <aoo@student.42singapore.sg>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 19:33:28 by aoo               #+#    #+#             */
/*   Updated: 2025/02/11 14:01:04 by aoo              ###   ########.fr       */
>>>>>>> 4cdeb0f6219f9fcf8d9941a671c90a0876c7291f
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*replace_env(char *str, char **result, t_list *envp, int status)
{
	char	*start;
	char	*s_value;

	start = ++str;
	if (*start == '?')
	{
		s_value = ft_itoa(status);
		*result = ft_strjoin(*result, s_value, 1, 1);
		return (++str);
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

char	*handle_env(char *str, t_list *envp, int status)
{
	char	*result;
	int     in_quote;
	int		here_doc;

	in_quote = 0;
	result = NULL;
	here_doc = 0;
	while (str && *str)
	{
		if (*str == '\\' && *(str + 1) && in_quote != '\'')
		{
			result = ft_strcjoin(result, *str++);
			result = ft_strcjoin(result, *str++);
		}
		is_quote("\'\"", *str, &in_quote);
		if (!in_quote && !ft_strncmp("<<", str, 2))
			here_doc = 1;
		if (here_doc && *str == ' ')
			here_doc = 0;
		if (!here_doc && *str == '$' && in_quote != '\'')
			str = replace_env(str, &result, envp, status);
		else
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
<<<<<<< HEAD
		*result = ft_strcjoin(*result, *str++);
=======
	{
		if (*str == '\\')
			str = handle_esc(str, result, 1);
		else
			*result = ft_strcjoin(*result, *str++);
	}
>>>>>>> 4cdeb0f6219f9fcf8d9941a671c90a0876c7291f
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
<<<<<<< HEAD
		if (*str == '\'')
=======
		if (*str == '\\')
			str = handle_esc(str, &result, 0);
		else if (*str == '\'')
>>>>>>> 4cdeb0f6219f9fcf8d9941a671c90a0876c7291f
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
