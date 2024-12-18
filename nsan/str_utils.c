/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsan <nsan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 17:01:19 by nsan              #+#    #+#             */
/*   Updated: 2024/12/17 18:04:13 by nsan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void detect_str(char *str, t_tokens tokens)
{
	int i;
	int word = 0;

	i = 0;
	while(str[i] != '\0')
	{
		if((str[i] >= 'a' && str[i] <= 'z') && str[i+1] == '\0' || (str[i] == '\"'))
		{
			tokens.tok_types = T_WORD;
			word++;
		}
		else if(str[i] == '>')
			tokens.tok_types = T_REDIRECT_OUT;
		i++;
	}
	if(!ft_strncmp(str, "|", 1))
		tokens.tok_types = T_PIPE;
	else if(!ft_strncmp(str, ">", 1))
		tokens.tok_types = T_REDIRECT_OUT;
	else if(!ft_strncmp(str, "<", 1))
		tokens.tok_types = T_REDIRECT_IN;
	else if(!ft_strncmp(str, ">>", 2))
		tokens.tok_types = T_APPEND;
	else if(!ft_strncmp(str, "<<", 2))
		tokens.tok_types = T_HERE_DOCS;
	else if(!ft_strncmp(str, "$", 1))
		tokens.tok_types = T_VAR;
	printf("[ %s ] token : %d\n", str, tokens.tok_types);
}

t_tokens *create_new_token(char *str){
	t_tokens *token_malloc = malloc(sizeof(t_tokens));
	token_malloc->str = ft_strdup(str);
	token_malloc->next = NULL;
	return (token_malloc);
}

void tokenize_str(t_tokens *new_token, char *str){
	int i;
	int word = 0;

	i = 0;
	while(str[i] != '\0')
	{
		if((str[i] >= 'a' && str[i] <= 'z') && str[i+1] == '\0' || (str[i] == '\"'))
		{
			new_token->tok_types = T_WORD;
			word++;
		}
		else if(str[i] == '>')
			new_token->tok_types = T_REDIRECT_OUT;
		i++;
	}
	if(!ft_strncmp(str, "|", 1))
		new_token->tok_types = T_PIPE;
	else if(!ft_strncmp(str, ">", 1))
		new_token->tok_types = T_REDIRECT_OUT;
	else if(!ft_strncmp(str, "<", 1))
		new_token->tok_types = T_REDIRECT_IN;
	else if(!ft_strncmp(str, ">>", 2))
		new_token->tok_types = T_APPEND;
	else if(!ft_strncmp(str, "<<", 2))
		new_token->tok_types = T_HERE_DOCS;
	else if(!ft_strncmp(str, "$", 1))
		new_token->tok_types = T_VAR;
	// return (token)
	// printf("[ %s ] token : %d\n", token_malloc->str, token_malloc->tok_types);
}

void	ft_lstadd_back(t_tokens **lst, t_tokens *new)
{
	t_tokens	*current;

	if (!new)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		current = *lst;
		while (current->next)
			current = current->next;
		current->next = new;
	}
}