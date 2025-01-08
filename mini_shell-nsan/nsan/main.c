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
		write(1, "minishell> \n", 14);
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
	t_ast *ast_node;
	t_tokens tokens;
	t_tokens **whole_list;
	char buf[1024];
	int	i;
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
				ast_node = ast(whole_list);
			if(ast_node && (ast_node->right)->cmd)
			{
				printf("right cmd list :\n");
				char **right_cmd = (ast_node->right)->cmd;
				while (*right_cmd) {
					printf("%s\n", *right_cmd);
					right_cmd++;
				}
			}
			if (ast_node && (ast_node->left)->cmd)
			{
				printf("left cmd list :\n");
				char **left_cmd = (ast_node->left)->cmd;
				while (*left_cmd) {
					printf("%s\n", *left_cmd);
					left_cmd++;
				}
			}
			if(!input)
				printf("no input to add for history");
			else
			{
				add_history(input);
				int open_fd = open(".mini_history", O_RDWR|O_CREAT|O_APPEND, 0666);
				int write_fd = write(open_fd, input, ft_strlen(input));
				write(open_fd, "\n", 1);
				if(open_fd == -1)
					printf("open error\n");
				if(write_fd == -1)
					printf("write error\n");
				if(!ft_strncmp(input, "history", 7))
				{
					int sz;
					int another_fd = open(".mini_history", O_RDONLY);
					sz = read(another_fd, buf, sizeof(buf)-1);
					if(sz > 0)
					{
						handle_newline(buf, sz);
						buf[sz] = '\0';
					}
					if (sz < 0) {
						perror("Error reading file");
					}
				}
				close(open_fd);
			}
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