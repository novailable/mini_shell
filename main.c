/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 16:39:37 by nsan              #+#    #+#             */
/*   Updated: 2025/02/03 18:10:53 by marvin           ###   ########.fr       */
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
		signal_handling();
		char *input = readline("minishell % ");
		if (input && (*input != '|'))
		{
			history_output(input);
			tokens = custom_split(input);

			// t_tokens *current = tokens;
			// int j = 0;
			// while (current != NULL) {
			// 	printf("String: %s\n", current->str);
			// 	current = current->next;
			// 	j++;
			// }
			tokenize_str(tokens);
			t_tokens *current = tokens;
				int j = 0;
			while (current != NULL) 
			{
				printf("%s, %d\n", current->str, current->tok_types);
				current = current->next;
				j++;
			}
			if(check_grammar_syntax(tokens))
			{
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
			}
			free_tokens(tokens);
	// 	else
	// 		printf("Error reading input.\n");
		}
		else if(input == NULL)
		{
			printf("<<minishell has exited >>");
			return (0);
		}
	}
	// ft_lstclear(&envp, free_envp);
	return 0;
}



			// if (!is_balanced_quotes(input))
			// {
			// 	perror("unclosed quotation");
			// 	continue;
				// char *remainder = ft_strrchr(input, '\"');
				// if(ft_strncmp(input, "echo", 4) == 0)
				// {
				// 	char *new_dest = new_line_input(0, NULL);
				// 	printf("%s\n%s", remainder, new_dest);
				// }
				// else
				// {
				// 	char *new_dest = new_line_input(0, NULL);
				// 	printf("%s\n%s not found\n", remainder, new_dest);
				// }
				// free(input);
			// }

/*print out the whole list*/
// t_tokens *current = *whole_list;
// 	int j = 0;
// 	while (current != NULL) {
// 		printf("Content %d:\n", j);
// 		printf("String: %s\n", current->str);
// 		printf("Token: %u\n\n", current->tok_types);
// 		current = current->next;
// 		j++;
// 	}

/*print for the ast_node_cmds*/
// if(ast_node && (ast_node->right)->cmd)
			// {custom_split
			// if (ast_node && (ast_node->left)->cmd)
			// {
			// 	printf("left cmd list :\n");
			// 	char **left_cmd = (ast_node->left)->cmd;
			// 	while (*left_cmd) {
			// 		printf("%s\n", *left_cmd);
			// 		left_cmd++;
			// 	}
			// }

	/*debug printing*/
			// print_rightmost_command(ast_node);
			// if (ast_node && ast_node->right) {
			// 	printf("The right-cmd-node branch exists\n");

			// 	t_ast *right_node = ast_node->right;
			// 	t_ast *cmd_node = right_node->left;

			// 	// Ensure right_node and cmd_node exist
			// 	if (cmd_node && cmd_node->right) {
			// 		char **temp_str = cmd_node->right->cmd;

			// 		if (temp_str) {
			// 			printf("temp_str exists\n");
			// 			while (*temp_str) {
			// 				printf("cmd of the right node of the left-cmd-node branch: %s\n", *temp_str);
			// 				temp_str++;
			// 			}
			// 		} else {
			// 			printf("temp_str is NULL (no commands in this branch)\n");
			// 		}
			// 	} else {
			// 		printf("cmd_node or cmd_node->right is NULL\n");
			// 	}
			// } else {
			// 	printf("The right-cmd-node branch does not exist\n");
			// }

				// if(right_node->right)
				// {
				// 	temp_str = right_node->right->cmd;
					// while(*temp_str)
					// {
					// 	printf("cmd of the right node of the left-cmd-node branch: %s\n", *temp_str);
					// 	temp_str++;
					// }

				// }

			// }
			// if (ast_node && (ast_node->left)->cmd)
			// {
			// 	printf("left cmd list :\n");
			// 	char **left_cmd = (ast_node->left)->cmd;
			// 	while (*left_cmd) {
			// 		printf("%s\n", *left_cmd);
			// 		left_cmd++;
			// 	}
			// }

			/*<<<---->>>>*/
