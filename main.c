/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 16:39:37 by nsan              #+#    #+#             */
/*   Updated: 2025/02/05 16:45:17 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



int is_balanced_quotes(char *input)
{
	int single_quote;
	int double_quote;

	single_quote = 0;
	double_quote = 0;
	while (*input)
	{
		if (*input == '\'' && double_quote == 0)
			single_quote = !single_quote;
		else if (*input == '"' && single_quote == 0)
			double_quote = !double_quote;
		input++;
	}
	return (single_quote == 0 && double_quote == 0);
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
	envp = init_envp(envpath);
	while (1)
	{
		// signal_handling();
		char *input = readline("minishell % ");
		if (input && (*input != '|'))
		{
			history_output(input);
			if(is_balanced_quotes(input))
			{
				tokens = string_split(input);
				tokenize_str(tokens);
				// print_tokens(tokens);
				if(check_grammar_syntax(tokens, input))
				{
					ast_node = malloc(sizeof(t_ast));
					if (!ast_node)
						printf("Error in main_ast malloc\n");
					ast(ast_node, tokens);
					if(ast_node)
						print_ast(ast_node);
						printf("%d\n", execute_ast(ast_node, envp, status));	
					free_ast(ast_node);
					free(ast_node);
					free(input);
				}
				free_tokens(tokens);
			}
			else
			{
				printf("quotes not balanced\n");
				return (0);
			}
		}
		else if(input == NULL)
		{
			printf("<< minishell has exited >>\n");
			return (0);
		}
		else
			printf("| cannot be at the beginning of cmd\n");
	}
	ft_lstclear(&envp, free_envp);
	return (0);
}


