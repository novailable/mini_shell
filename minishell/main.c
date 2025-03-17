/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoo <aoo@student.42singapore.sg>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:51:21 by aoo               #+#    #+#             */
/*   Updated: 2025/03/17 13:39:29 by aoo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tokens(t_tokens *head, char *str)
{
	t_tokens	*current;

	current = head;
	printf("%s: ", str);
	if (head == NULL)
		printf("NULL");
	while (current)
	{
		printf("{");
		for (int i = 0; current->str[i]; i++)
		{
			if (current->str[i] == QUOTE_MARKER)
				printf("ç");
			else
				printf("%c", current->str[i]);
		}
		printf(", %d} ", current->tok_types);
		current = current->next;
	}
	printf("\n\n");
}

int	is_in_quote(char *str)
{
	int	i;
	int	in_quote;

	i = 0;
	in_quote = 0;
	while (str[i])
	{
		is_quote("\'\"", str[i], &in_quote);
		i++;
	}
	return (in_quote);
}

int	get_input(t_core *core)
{
	char	*input;

	(signal(SIGINT, handle_sigint), signal(SIGQUIT, SIG_IGN));
	input = readline("minishell % ");
	get_interrupt(core);
	if (input && *input != '|' && *input != '\0')
	{
		add_history(input);
		if (is_in_quote(input))
		{
			core->input = input;
			print_err_msg("unclosed quote\n", NULL, NULL);
			core->status = 1;
			return (1);
		}
	}
	else
	{
		if (input && *input == '|')
			core->status = 2;
		return (core->input = input, 1);
	}
	core->input = input;
	return (0);
}

int	init_token(t_core *core)
{
	core->tokens = string_split(core->input, 0, 1);
	if (!core->tokens)
		return (1);
	tokenize_str(core->tokens);
	if (check_grammar_syntax(core->tokens) == 1)
	{
		token_expansion(core);
		// print_tokens(core->tokens, "expan : ");
		token_split(core);
		// print_tokens(core->tokens, "after split : ");
		prepare_heredoc(core);
		// print_tokens(core->tokens, "after heredoc : ");
		if (get_interrupt(core))
			return (free_tokens(&core->tokens), free_str(&core->input), 1);
		if (check_tokens(core))
			return (core->status = 1, free_tokens(&core->tokens), \
					free_str(&core->input), 1);
	}
	else
	{
		core->status = 2;
		return (free_tokens(&core->tokens), free_str(&core->input), 1);
	}
	if (core->tokens == NULL && core->input)
		core->status = 0;
	free_str(&core->input);
	return (0);
}

int	main(int argc, char **argv, char **envpath)
{
	t_core	*core;
	int		status;

	((void)argc, (void)argv);
	core = init_core(envpath);
	while (1)
	{
		if (get_input(core))
		{
			status = core->status;
			if (core->input == NULL)
				return (ft_putstr_fd("exit\n", 2), \
				free_str(&core->input), free_core(core), status);
			else if (*core->input == '|')
				print_err_msg(" syntax error near unexpected token `|'\n", NULL,
					NULL);
			free_str(&core->input);
			continue ;
		}
		if (init_token(core))
			continue ;
		if (init_ast(core) && core->ast)
			(execute_ast(core), free_ast(&core->ast));
	}
	return (free_core(core), 0);
}
