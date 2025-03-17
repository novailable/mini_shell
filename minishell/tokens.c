/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsan <nsan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 17:30:16 by nsan              #+#    #+#             */
/*   Updated: 2025/03/11 17:30:16 by nsan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_add_token(t_tokens **head, char *str, int type)
{
	if (str && *str && *str != ' ')
		append_token(head, create_new_token(str, type));
	if (str)
		free(str);
}

int	special_char_check(char curr_c, char next_c, char *str, t_tokens **head)
{
	if (curr_c == next_c && curr_c != '|')
		return (create_add_token(head, ft_strndup(str, 2), 0), 1);
	else
		return (create_add_token(head, ft_strndup(str, 1), 0), 0);
}

void	handle_special_char(char *input, t_tokens **head, char **start, int *i)
{
	create_add_token(head, ft_strndup(*start, (input + *i) - *start), 0);
	*start = input + *i;
	*i += special_char_check(input[*i], input[*i + 1], *start, head);
	*start = input + *i + 1;
}

t_tokens	*string_split(char *input, int type, int spec_split)
{
	t_tokens	*head;
	char		*start;
	int			start_quote;
	int			i;

	head = NULL;
	start = input;
	start_quote = 0;
	i = -1;
	while (input && input[++i])
	{
		if (!is_quote("\"\'", input[i], &start_quote) && \
		ft_strchr(" \t", input[i]))
		{
			create_add_token(&head, ft_strndup(start, \
						(input + i) - start), type);
			start = input + i + 1;
		}
		else if (spec_split && input[i] && \
			ft_strchr("<>|", input[i]) && !start_quote)
			handle_special_char(input, &head, &start, &i);
	}
	if (start && *start)
		create_add_token(&head, ft_strdup(start), type);
	return (head);
}
