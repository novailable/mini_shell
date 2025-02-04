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
    int start_quote;
    int len;
    int flag;

    i = 0;
    head = NULL;
    flag = 0;
    len = 0;
    str = ft_strdup("");
    while (input[i] != '\0')
    {    
        //take out the substring for the "a > b"
        if(input[i] == '\"' || input[i] == '\'')
        {
            if(flag == 0)
            {
                start_quote = i;
                flag = 1;
            }
            else
                len = i + 1;   
        }
        else if ((input[i] == '<' || input[i] == '>' || input[i] == '|') && flag == 0) 
        {
            if (special_char_check(input[i], input[i+1], &str, &head))
                i++;
        }
        else if (input[i] != ' ' && flag == 0) 
            str = ft_strcjoin(str, input[i]);
        else if (*str != '\0') 
            create_add_token(&head, &str);

        if(flag == 1 && len > 0)
        {
            str = ft_substr(input, start_quote, len);
            create_add_token(&head, &str);
            str = ft_strdup("");
            flag = 0;
        }    
        i++;
    }
    if (*str != '\0')
        append_token(&head, create_new_token(str));
    free(str);
    return (head);
}

//check whether the single and double quotation has pairs in the check_grammar_syntax