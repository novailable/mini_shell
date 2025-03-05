/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 16:39:37 by nsan              #+#    #+#             */
/*   Updated: 2025/02/19 18:23:33 by aoo              ###   ########.fr       */
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

	printf("Token: ");
	while (current)
	{
		printf("{%s} ", current->str);
		current = current->next;
	}
	printf("\n");
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
	t_ast *ast_node;
	t_tokens	*tokens;
	t_list	*envp;
	int		status;

	((void)argc, (void)argv);
	
	envp = init_envp(envpath);
	status = 0;
	while (1)
	{
		set_signal();
		char *input = readline(PROMPT);
		if (g_sig_interrupt)
		{
			status = 130;
			g_sig_interrupt = 0;
		}
		if (input && *input != '|' && *input != '\0')
		{
			history_write(input);
			if (!is_in_quote(input))
			{
				tokens = string_split(handle_env(input, envp, status));
				tokenize_str(tokens);
				prepare_heredoc(tokens, envp, status);
				if (g_sig_interrupt)
				{
					status = 130;
					g_sig_interrupt = 0;
					continue ;
				}
				// print_tokens(tokens);
				if(check_grammar_syntax(tokens, input))
				{
					
					ast_node = malloc(sizeof(t_ast));
					if (!ast_node)
						printf("Error in main_ast malloc\n");
					ast(ast_node, tokens);
					// if(ast_node)
						// print_ast(ast_node);
					status = execute_ast(ast_node, envp, status);	
					free_tokens_ast(tokens, ast_node);
				}
				else
					free_tokens(tokens);
			}
			else
			{
				free(input);
				write(2, "minishell: unclosed quote\n", 27);
				status = 1;
				continue;
			}
		}	
		else if(input == NULL)
			return (ret_free_envp("<< exit >>\n", envp, NULL), 0);
		else if(*input == '|')
			printf("minishell: syntax error near unexpected token `|'\n");
	}
	ft_lstclear(&envp, free_envp);
	return (0);
}


