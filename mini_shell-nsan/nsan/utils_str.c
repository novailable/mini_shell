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
	else if(!ft_strncmp(str, ">>", 2))
		new_token->tok_types = T_APPEND;
	else if(!ft_strncmp(str, "<<", 2))
		new_token->tok_types = T_HERE_DOCS;
	else if(!ft_strncmp(str, ">", 1))
		new_token->tok_types = T_REDIRECT_OUT;
	else if(!ft_strncmp(str, "<", 1))
		new_token->tok_types = T_REDIRECT_IN;
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

int quote_check(const char *input_str)
{	
	int flag = 0;
	int i = 0;
	while(input_str[i])
	{
		if(input_str[i] == '\"')
			return (1);
		i++;
	}
	return (0);
}

char *new_line_input(int flag, char *delimeter) //delimeter has "some word"
{
	char *output;
	char *new_line;
	char *next_input;
	char *input = readline(">");

	// printf("input%s", input);
	if(flag == 0)
	{
		if (!quote_check(input))
		{
			new_line = ft_strjoin(input, "\n");
			free(input);
			input = new_line;
			next_input = new_line_input(0, NULL);
			output = ft_strjoin(input, next_input);
		}
		else
		{
			if(ft_strncmp(input, "\"", 1) == 0)
				input[0] = '\0';
			output = input;
		}
	}
	else if(flag == 1)
	{
		int word_len = ft_strlen(delimeter);
		if(ft_strncmp(input, delimeter, word_len))
		{
			new_line = ft_strjoin(input, "\n");
			free(input);
			input = new_line;
			next_input = new_line_input(1, delimeter);
			output = ft_strjoin(input, next_input);
		}
		else
		{
			if(ft_strncmp(input, delimeter, word_len) == 0)
				input[0] = '\0';
			output = input;
		}
	}
	return (output);
}

void handle_newline(char *buf, int sz)
{
	int i = -1;
	while(++i < sz)
	{
		if(buf[i] != '\n')
			write(1, &buf[i], 1);
		else
			write(1, "\n", 1);
	}
	
}