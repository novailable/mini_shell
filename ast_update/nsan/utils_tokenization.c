/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 20:54:08 by nsan              #+#    #+#             */
/*   Updated: 2024/12/18 11:29:19 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tokens **tokenization(char **dest, int count)
{
	t_tokens *new_token;
	t_tokens **whole_list = malloc(sizeof(t_tokens *) * count);
	int i;

	i = 0;
	*whole_list = NULL;
	while (dest[i] != NULL)
	{
		new_token = create_new_token(dest[i]);
		tokenize_str(new_token, dest[i]);
		ft_lstadd_back(whole_list, new_token);
		i++;
	}
	/*print out the whole list ["ls", "-l"] and its details*/
	// t_tokens *current = *whole_list;
	// int j = 0;
	// while (current != NULL)
	// {
	// 		printf("Content %d:\n", j);
	// 		printf("String: %s\n", current->str);
	// 		printf("Token: %u\n\n", current->tok_types);
	// 		current = current->next;
	// 		j++;
	// }
	return (whole_list);
}

int check_grammar_syntax(t_tokens **whole_list)
{
    t_tokens *temp;
	if (!whole_list || !*whole_list) // Check if the list is NULL
    {
        printf("Invalid input: whole_list is NULL\n");
        return (0);
    }
    temp = *whole_list;
    while (temp)
    {
        if (temp->tok_types == T_WORD)
        {
            // A word can be followed by another word, a pipe, or a redirect
			if(temp->next == NULL)
				break;
            if (temp->next->tok_types != T_WORD &&
                temp->next->tok_types != T_PIPE &&
                temp->next->tok_types != T_REDIRECT_OUT)
            {
                printf("Invalid syntax after T_WORD\n");
                return (0);
            }
        }
        else if (temp->tok_types == T_PIPE)
        {
            // A pipe must be followed by a word
            if (temp->next == NULL || temp->next->tok_types != T_WORD)
            {
                printf("Invalid syntax after T_PIPE\n");
                return (0);
            }
        }
        else if (temp->tok_types == T_REDIRECT_IN || temp->tok_types == T_REDIRECT_OUT)
        {
            // Redirects must be followed by a word
            if (temp->next == NULL || temp->next->tok_types != T_WORD)
            {
                printf("Invalid syntax after redirect\n");
                return (0);
            }
        }

        // Move to the next token
        temp = temp->next;
    }

    // If we reach here, the syntax is valid
    printf("Syntax is valid\n");
    return (1);
}

