<<<<<<< HEAD
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsan <nsan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 07:18:09 by nsan              #+#    #+#             */
/*   Updated: 2025/01/14 07:18:09 by nsan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	args_list_len_alloc(t_tokens *whole_list, char ***args_list)
{
	t_tokens	*current;
	int			args_len;

	args_len = 0;
	current = whole_list;
	while (current && current->tok_types != T_PIPE)
	{
		if (current->tok_types == T_WORD)
			args_len++;
		else if (current->tok_types == T_REDIRECT_OUT || \
		current->tok_types == T_REDIRECT_IN || \
		current->tok_types == T_APPEND)
		{
			if (current->next->tok_types == T_WORD)
				current = current->next;
		}
		current = current->next;
	}
	if (args_len == 0)
	{
		*args_list = NULL;
		return ;
	}
	*args_list = malloc(sizeof(char *) * (args_len + 1));
}
=======
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsan <nsan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 07:18:09 by nsan              #+#    #+#             */
/*   Updated: 2025/01/14 07:18:09 by nsan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	args_list_len_alloc(t_tokens *whole_list, char ***args_list)
{
	t_tokens	*current;
	int			args_len;

	args_len = 0;
	current = whole_list;
	while (current && current->tok_types != T_PIPE)
	{
		if (current->tok_types == T_WORD)
			args_len++;
		else if (current->tok_types == T_REDIRECT_OUT || \
		current->tok_types == T_REDIRECT_IN || \
		current->tok_types == T_APPEND)
		{
			if (current->next->tok_types == T_WORD)
				current = current->next;
		}
		current = current->next;
	}
	if (args_len == 0)
	{
		*args_list = NULL;
		return ;
	}
	*args_list = malloc(sizeof(char *) * (args_len + 1));
}
>>>>>>> 4cdeb0f6219f9fcf8d9941a671c90a0876c7291f
