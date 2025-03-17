/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_token2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoo <aoo@student.42singapore.sg>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 18:25:48 by aoo               #+#    #+#             */
/*   Updated: 2025/03/17 11:24:34 by aoo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_token_str(t_tokens *current, t_core *core, \
						int pre_type, int is_export)
{
	char	*temp;

	if (pre_type != T_HERE_DOCS && !is_export)
	{
		temp = current->str;
		current->str = handle_env(current->str, core);
		free(temp);
	}
}

void	token_expansion(t_core *core)
{
	t_tokens	*current;
	int			pre_type;
	int			is_export;

	pre_type = 0;
	is_export = 0;
	current = core->tokens;
	while (current)
	{
		if (!is_export && !ft_strcmp("export", current->str))
			is_export = 1;
		if (current->tok_types == 0)
			replace_token_str(current, core, pre_type, is_export);
		if (current->tok_types == T_PIPE)
			is_export = 0;
		pre_type = current->tok_types;
		current = current->next;
	}
}

void	token_split(t_core *core)
{
	t_tokens	*temp;
	t_tokens	*temp_head;
	t_tokens	*current;

	temp = NULL;
	temp_head = NULL;
	current = core->tokens;
	while (current)
	{
		temp = string_split(current->str, current->tok_types, 0);
		append_token(&temp_head, temp);
		current = current->next;
	}
	free_tokens(&core->tokens);
	core->tokens = temp_head;
}

int	check_tokens(t_core *core)
{
	t_tokens	*current;
	int			type;

	current = core->tokens;
	while (current)
	{
		type = current->tok_types;
		if (type == T_REDIRECT_IN || type == T_REDIRECT_OUT || type == T_APPEND)
		{
			if (!current->next)
				return (print_err_msg(": ambiguous redirect\n", NULL, NULL), 1);
		}
		current = current->next;
	}
	return (0);
}
