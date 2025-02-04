/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 19:47:28 by marvin            #+#    #+#             */
/*   Updated: 2025/02/03 19:47:28 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void create_add_token(t_tokens **head, char **str)
{
    append_token(head, create_new_token(*str));
    free(*str);
    *str = ft_strdup("");
}

int special_char_check(char curr_c, char next_c, char **str, t_tokens **head)
{
    if (**str != '\0')
        create_add_token(head, str);
    if ((curr_c == '<' && next_c == '<') \
    || (curr_c == '>' && next_c == '>')) 
    {
        *str = ft_strcjoin(*str, curr_c);
        *str = ft_strcjoin(*str, next_c);
        create_add_token(head, str);
        return (1);
    }
    else 
    {
        *str = ft_strcjoin(*str, curr_c);
        create_add_token(head, str);
    }
    return (0);
}

t_tokens *string_split(char *input) 
{
    int i;
    t_tokens *head;
    char *str;

    i = 0;
    head = NULL;
    str = ft_strdup("");
    while (input[i] != '\0')
    {    
        if (input[i] == '<' || input[i] == '>' || input[i] == '|') 
        {
            if (special_char_check(input[i], input[i+1], &str, &head))
                i++;
        }
        else if (input[i] != ' ') 
            str = ft_strcjoin(str, input[i]);
        else if (*str != '\0') 
            create_add_token(&head, &str);
        i++;
    }
    if (*str != '\0')
        append_token(&head, create_new_token(str));
    free(str);
    return (head);
}


// Print tokens
//     t_tokens *current = head;
//     while (current) 
//     {
//         printf("string: %s\n", current->str);
//         current = current->next;
//     }
//check whether the single and double quotation has pairs in the check_grammar_syntax