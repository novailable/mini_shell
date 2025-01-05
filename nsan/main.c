/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 16:39:37 by nsan              #+#    #+#             */
/*   Updated: 2024/12/18 11:26:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handle_signal(int sig)
{
	if(sig == SIGINT)
	{
		write(1, "minishell> \n", 13);
		rl_on_new_line();
		rl_redisplay();
	}
}

void handle_new_print_line(int sig)
{
	if(sig == SIGINT)
	{
		write(1, ">\n", 3);
		rl_on_new_line();
		rl_redisplay();
	}
}

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

char **custom_split(const char *input) {
	int i = 0, start = 0, j = 0;
	char **tokens = malloc(sizeof(char *) * (ft_strlen(input) + 1));
	int single_quote = 0, double_quote = 0;

	while (input[i]) {
		if (input[i] == '\'' && double_quote == 0)
			single_quote = !single_quote;
		else if (input[i] == '"' && single_quote == 0)
			double_quote = !double_quote;
		else if (input[i] == ' ' && single_quote == 0 && double_quote == 0) {
			if (i > start) {
				tokens[j++] = strndup(input + start, i - start);
			}
			start = i + 1;
		}
		i++;
	}
	if (i > start) {
		tokens[j++] = strndup(input + start, i - start);
	}
	tokens[j] = NULL;
	return tokens;
}

void free_tokens(char **tokens) {
	int i = 0;
	while (tokens[i])
		free(tokens[i++]);
	free(tokens);
}

int main() {
	struct sigaction sa_int;
	struct sigaction sa_newline;
	char **dest;
	t_tokens tokens;
	t_tokens **whole_list;
	int	i;
	// char *word1 = "hello";
	// char *word2 = "world";
	// char *new_dest = ft_strjoin(word1, word2);
	// printf("%s\n", new_dest);
	while (1)
	{
		sa_int.sa_handler = handle_signal;
		
		if (sigaction(SIGINT, &sa_int, NULL) == -1)
			printf("Sigaction failed\n");
		sigemptyset(&sa_int.sa_mask);

		// sa_newline.sa_handler = handle_new_print_line;
		// sigemptyset(&sa_newline.sa_mask);

		char *input = readline("minishell> ");
		if (input && (*input != '|')) {
			if (!is_balanced_quotes(input))
			{
				char *remainder = ft_strrchr(input, '\"');
				if(ft_strncmp(input, "echo", 4) == 0)
				{
					char *new_dest = new_line_input(0, NULL);
					printf("%s\n%s", remainder, new_dest);
				}
				else
				{
					char *new_dest = new_line_input(0, NULL);
					printf("%s\n%s not found\n", remainder, new_dest);
				}
				free(input);
				continue;
			}
			dest = custom_split(input);
			i = 0;
			while (dest[i])
				i++;
			whole_list = tokenization(dest, i);
			if(check_grammar_syntax(whole_list)) 
				ast(whole_list);
			add_history(input);
		} else if (!input)
			break;
		else 
			printf("Error reading input.\n");
	}
	return 0;
}

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