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

t_ast *ast(t_tokens **whole_list)
{
	int i;
	t_ast *ast_node;
	t_tokens *current;
	int flag = 0;

	i = 0;
	ast_node = NULL;
	current = *whole_list;
	if(current == NULL)
		return NULL;
	while(current != NULL)
	{
		if(ft_strncmp(current->str, "|", 1) == 0)
		{
			flag = 1;
			return(parse_pipe(whole_list), ast_node);
		}
		else if (ft_strncmp(current->str, ">>", 2) == 0){
			flag = 1;
			return(parse_redirect(whole_list, 1), ast_node);
		}
		else if (ft_strncmp(current->str, "<<", 2) == 0){
			flag = 1;
			new_line_input(1, current->next->str);
		}
		else if(ft_strncmp(current->str, "<", 1) == 0)
		{
			flag = 1;
			return(parse_redirect(whole_list, 0), ast_node);
		}
		else if (ft_strncmp(current->str, ">", 1) == 0){
			flag = 1;
			return(parse_redirect(whole_list, 1), ast_node);
		}
		else
			flag = 0;
		current = current->next;
	}
	if(!flag)
		return(parse_cmd(ast_node, whole_list, NULL));
	return (ast_node);
}

int check_grammar_syntax(t_tokens **whole_list)
{
    t_tokens *temp;
	int	flag;

	flag = 0;
	temp = *whole_list;
    while (temp)
    {
        if (temp->tok_types == T_WORD) {
			if((temp->next != NULL && temp->next->tok_types == T_WORD) ||
			(temp->next != NULL && temp->next->tok_types == T_PIPE) ||
			(temp->next != NULL && temp->next->tok_types == T_REDIRECT_OUT))
				return (1);
        }
		else if(temp->tok_types == T_PIPE)
		{
			if((temp->next == NULL) ||
			(temp->next != NULL && temp->next->tok_types == T_WORD))
				return (1);
		}
		else if(temp->tok_types == T_REDIRECT_IN || temp->tok_types == T_REDIRECT_OUT)
		{
			if(temp->next != NULL && temp->next->tok_types == T_WORD)
				return (1);
		}
        temp = temp->next;
    }
	return (0);
    printf("reached end\n");
}
