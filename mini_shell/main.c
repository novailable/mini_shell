#include "minishell.h"

void	print_tokens(t_tokens *head)
{
	t_tokens	*current = head;

	printf("Token: ");
	if (head == NULL)
		printf("NULL");
	while (current)
	{
		printf("{%s} ", current->str);
		current = current->next;
	}
	printf("\n");
}

t_core	*init_core(char **envpath)
{
	t_core	*core;

	core = (t_core *)malloc(sizeof(t_core));
	if (!core)
		return (NULL);
	core->envp = init_envp(envpath);
	core->tokens = NULL;
	core->ast = NULL;
	core->input = NULL;
	core->status = 0;
	return (core);
}

int	get_input(t_core *core)
{
	char *input;

	(signal(SIGINT, handle_sigint),	signal(SIGQUIT, SIG_IGN));
	input = readline(PROMPT);
	get_interrupt(core);
	if (input && *input != '|' && *input != '\0')
	{
		history_write(input);
		if (is_in_quote(input))
		{
			free(input);
			print_err_msg("unclosed quote\n");
			core->status= 1;
			return (1);
		}
	}
	else
		return (core->input = input, 1);
	core->input = input;
	return (0);
}

int	init_token(t_core *core)
{
	core->tokens = string_split(handle_env(core->input, core));
	free(core->input);
	core->input = NULL;
	if (!core->tokens)
		return (1);
	tokenize_str(core->tokens);
	if (check_grammar_syntax(core->tokens))
	{
		prepare_heredoc(core);
		if (get_interrupt(core))
			return (1);
	}
	else
		return (free_tokens(&core->tokens), 1);
	return (0);
}

int	main(int argc, char **argv, char **envpath)
{
	t_core		*core;
	char		*input;

	((void)argc, (void)argv);
	core = init_core(envpath);
	while (1)
	{
		if (get_input(core))
		{
			if (core->input == NULL)
				return (ft_putstr_fd("<< exit >>\n", 2), free_core(core), 0);
			else if (*core->input == '|')
				print_err_msg(" syntax error near unexpected token `|'\n");
			continue ;
		}
		if (init_token(core))
			continue ;
		init_ast(core);
		if (core->ast)
		{
			execute_ast(core);
			free_ast(&core->ast);
		}
	}
	free_core(core);
	return (0);
}
