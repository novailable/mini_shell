/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoo <aoo@student.42singapore.sg>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 19:47:28 by marvin            #+#    #+#             */
/*   Updated: 2025/02/13 16:51:58 by aoo              ###   ########.fr       */
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

int	special_char_check(char curr_c, char next_c, char *str, t_tokens **head)
{
	if (curr_c == next_c && curr_c != '|')
		return (create_add_token(head, ft_strndup(str, 2)), 1);
	else
		return (create_add_token(head, ft_strndup(str, 1)), 0);
}

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
