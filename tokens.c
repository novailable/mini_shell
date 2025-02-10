/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoo <aoo@student.42singapore.sg>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 19:47:28 by marvin            #+#    #+#             */
/*   Updated: 2025/02/10 13:19:32 by aoo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_add_token(t_tokens **head, char *str)
{
	if (str && *str && *str != ' ')
		append_token(head, create_new_token(str));
	if (str)
		free(str);
}

// int special_char_check(char curr_c, char next_c, char **str, t_tokens **head)
// {
// 	if (**str != '\0')
// 		create_add_token(head, *str);
// 	if ((curr_c == '<' && next_c == '<') \
// 	|| (curr_c == '>' && next_c == '>')) 
// 	{
// 		*str = ft_strcjoin(*str, curr_c);
// 		*str = ft_strcjoin(*str, next_c);
// 		create_add_token(head, *str);
// 		return (1);
// 	}
// 	else 
// 	{
// 		*str = ft_strcjoin(*str, curr_c);
// 		create_add_token(head, *str);
// 	}
// 	return (0);
// }

int special_char_check(char curr_c, char next_c, char *str, t_tokens **head)
{
	if (curr_c == next_c && curr_c != '|')
		return (create_add_token(head, ft_strndup(str, 2)), 1);
	else
		return (create_add_token(head, ft_strndup(str, 1)), 0);
}

// int	special_char_check(t_tokens **head, char *input, int i, char **start)
// {
// 	if (ft_strchr("<>|", input[i]) )
// 	{
// 		create_add_token(head, ft_strndup(*start, (input + i) - *start));
// 		*start += i;
// 		if (input[i] == input[i + 1])
// 			(create_add_token(head, ft_strndup(*start, 2)), i++);
// 		else
// 			create_add_token(head, ft_strndup(*start, 1));
// 		*start += i + 1;
// 	}
// 	return (i);
// }

// t_tokens	*string_split(char *input)
// {
// 	int			i;
// 	t_tokens	*head;
// 	char		*str;
// 	int			start_quote;
// 	int			flag;

// 	i = 0;
// 	head = NULL;
// 	flag = 0;
// 	str = ft_strdup("");
// 	while (input[i] != '\0')
// 	{
// 		if ((input[i] == '\"' || input[i] == '\'') && flag == 0)
// 		{
// 			start_quote = i;
// 			flag = 1;
// 		}
// 		else if ((input[i] == '\"' || input[i] == '\'') && flag == 1)
// 		{
// 			str = ft_substr(input, start_quote, i + 1);
// 			create_add_token(&head, str);
// 			str = ft_strdup("");
// 			flag = 0;
// 		}
// 		else if ((input[i] == '<' || input[i] == '>' || \
// 		input[i] == '|') && flag == 0)
// 			i += special_char_check(input[i], input[i + 1], &str, &head);
// 		else if (input[i] != ' ' && flag == 0) 
// 			str = ft_strcjoin(str, input[i]);
// 		else if (*str != '\0') 
// 			create_add_token(&head, &str);
// 		i++;
// 	}
// 	if (*str != '\0')
// 		append_token(&head, create_new_token(str));
// 	(free(str), free(input));
// 	return (head);
// }

t_tokens	*string_split(char *input)
{
	int			i;
	t_tokens	*head;
	char		*start;
	int			start_quote;

	i = 0;
	head = NULL;
	start_quote = 0;
	start = input;
	while (input[i])
	{
		if (input[i] == '\\' && input[i + 1] && start_quote != '\'')
			i += 2;
		if (!is_quote("\"\'", input[i], &start_quote) && input[i] == ' ')
		{
			create_add_token(&head, ft_strndup(start, (input + i) - start));
			start = input + i + 1;
		}
		else if (ft_strchr("<>|", input[i]) && !start_quote)
		{
			create_add_token(&head, ft_strndup(start, (input + i) - start));
			start = input + i;
			i += special_char_check(input[i], input[i + 1], start, &head);
			start = input + i + 1;
		}
		i++;
	}
	if (start && *start)
		create_add_token(&head, ft_strdup(start));
	return (free(input), head);
}
//check whether the single and double quotation has pairs in the check_grammar_syntax
