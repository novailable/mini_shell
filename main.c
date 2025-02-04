/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 16:39:37 by nsan              #+#    #+#             */
/*   Updated: 2025/02/04 17:28:36 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



int is_balanced_quotes(const char *input) {
	int single_quote = 0, double_quote = 0;
	while (*input) {
		if (*input == '\'' && double_quote == 0)
			single_quote = !single_quote;
		else if (*input == '"' && single_quote == 0)
			double_quote = !double_quote;
		input++;
	}
	return single_quote == 0 && double_quote == 0;
}



void	print_tokens(t_tokens *head)
{
	t_tokens	*current = head;

	while (current)
	{
		printf("Token: %s\n", current->str);
		current = current->next;
	}
}

void	free_tokens(t_tokens *head)
{
	t_tokens	*temp;

	while (head)
	{
		temp = head;
		head = head->next;
		free(temp->str);
		free(temp);
	}
}

t_tokens	*custom_split(const char *input)
{
	int			i = 0;
	int			start = 0;
	int			single_quote = 0;
	int 		double_quote = 0;
	int			heredoc = 0;
	int			append = 0;
	t_tokens	*head = NULL;

	while (input[i])
	{
		if (input[i] == '\'' && !double_quote)
			single_quote = !single_quote;
		else if (input[i] == '"' && !single_quote)
			double_quote = !double_quote;
		else if(input[i] == '<' && input[i+1] == '<' && !single_quote && !double_quote)
		{
			if (i > start)
			{
				char *substr = ft_strndup(input + start, i - start);
				append_token(&head, create_new_token(substr));
				free(substr);
			}
			char *operator_token = ft_strndup(input + i, 2);
			heredoc = 1;
			append_token(&head, create_new_token(operator_token));
			free(operator_token);
			start = i + 2; // Move the start to the next character
		}
		else if(input[i] == '>' && input[i+1] == '>' && !single_quote && !double_quote)
		{
			if (i > start)
			{
				char *substr = ft_strndup(input + start, i - start);
				append_token(&head, create_new_token(substr));
				free(substr);
			}
			char *operator_token = ft_strndup(input + i, 2);
			append = 1;
			append_token(&head, create_new_token(operator_token));
			free(operator_token);
			start = i + 2; // Move the start to the next character
		}
		else if ((input[i] == '|' || input[i] == '>' || input[i] == '<' ) && !single_quote && !double_quote && !heredoc && !append && input[i+1] != ' ')
		{
			if (i > start)
			{
				char *substr = ft_strndup(input + start, i - start);
				append_token(&head, create_new_token(substr));
				free(substr);
			}
			char *operator_token = ft_strndup(input + i, 1);
			append_token(&head, create_new_token(operator_token));
			free(operator_token);

			start = i + 1;
		}
		else if ((input[i] == '|' || input[i] == '>' || input[i] == '<' ) && !single_quote && !double_quote && !heredoc && !append && input[i+1] == ' ')
		{
			if (i > start)
			{
				char *substr = ft_strndup(input + start, i - start);
				append_token(&head, create_new_token(substr));
				free(substr);
			}
			char *operator_token = ft_strndup(input + i, 1);
			append_token(&head, create_new_token(operator_token));
			free(operator_token);

			start = i + 1;
		}
		else if (input[i] == ' ' && !single_quote && !double_quote)
		{
			if (i > start)
			{
				char *substr = ft_strndup(input + start, i - start);
				append_token(&head, create_new_token(substr));
				free(substr);
			}
			start = i + 1;
		}
		// else if(input[i]) handle the operator when being followed after the letter/ word
		{
			
		}
		i++;
	}
	if (i > start)
	{
		char *substr = ft_strndup(input + start, i - start);
		append_token(&head, create_new_token(substr));
		free(substr);
	}
	return (head);
}

int main(int argc, char **argv, char **envpath)
{
	struct sigaction sa_int;
	struct sigaction sa_newline;
	t_ast *ast_node;
	t_tokens	*tokens;
	t_list	*envp;
	int		status;
	int	i;

	((void)argc, (void)argv);
	// envp = init_envp(envpath);
	while (1)
	{
		// signal_handling();
		char *input = readline("minishell % ");
		if (input && (*input != '|'))
		{
			history_output(input);
			tokens = string_split(input);
			
			// t_tokens *current = tokens;
			// int j = 0;
			// while (current != NULL) {
			// 	printf("String: %s\n", current->str);
			// 	current = current->next;
			// 	j++;
			// }
			tokenize_str(tokens);
			// t_tokens *current = tokens;
			// 	int j = 0;
			// while (current != NULL) 
			// {
			// 	printf("%s, %d\n", current->str, current->tok_types);
			// 	current = current->next;
			// 	j++;
			// }
			// if(check_grammar_syntax(tokens))
			// {
				ast_node = malloc(sizeof(t_ast));
				if (!ast_node)
					printf("Error in main_ast malloc\n");
				ast(ast_node, tokens);
				if(ast_node)
					print_ast(ast_node);
					// printf("%d\n", execute_ast(ast_node, envp, status));	
				free_ast(ast_node);
				free(ast_node);
				free(input);
	// 		}
			free_tokens(tokens);
		// else
		// 	printf("Error reading input.\n");
		}
		else if(input == NULL)
		{
			printf("<<minishell has exited >>");
			return (0);
		}
	}
	ft_lstclear(&envp, free_envp);
	return 0;
}




//splitting
