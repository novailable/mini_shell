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

// int main() {
// 	struct sigaction sa_int;
// 	char **dest;
// 	t_tokens tokens;

// 	while(1)
// 	{
// 		// signal(SIGINT, handle_signal);
// 		sa_int.sa_handler = handle_signal;
// 		if(sigaction(SIGINT, &sa_int, NULL) == -1)
// 			printf("Sigaction failed\n");
// 		sigemptyset(&sa_int.sa_mask);
// 		char *input = readline("minishell> ");

// 		if (input)
// 		{
// 			int i;

// 			i = 0;
// 			dest = ft_split(input, ' ');
// 			tokens.str = malloc(sizeof(char *) * strlen(input));
// 			while(dest[i] != NULL)
// 			{
// 				detect_str(dest[i], tokens);
// 				i++;
// 			}
// 			add_history(input);
// 			if(ft_strncmp(input, "clear", 5) == 0)
// 				rl_clear_history();
// 			free(input);
// 		}
// 		else if(!input)
// 			break;
// 		else {
// 			printf("Error reading input.\n");
// 		}

// 	}
// 	return 0;
// }


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
	char **tokens = malloc(sizeof(char *) * (strlen(input) + 1));
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
	char **dest;
	t_tokens tokens;
	int	i;

	while (1)
	{
		sa_int.sa_handler = handle_signal;
		if (sigaction(SIGINT, &sa_int, NULL) == -1)
			printf("Sigaction failed\n");
		sigemptyset(&sa_int.sa_mask);

		char *input = readline("minishell> ");
		if (input) {
			if (!is_balanced_quotes(input)) {
				printf("Error: Unmatched quotes\n");
				free(input);
				continue;
			}
			dest = custom_split(input);
			i = 0;
			while (dest[i])
				i++;
			tokenization(dest, i);
			add_history(input);
			if (strncmp(input, "clear", 5) == 0)
				rl_clear_history();
		} else if (!input) {
			break;
		} else {
			printf("Error reading input.\n");
		}
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