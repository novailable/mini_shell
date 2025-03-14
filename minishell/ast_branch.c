/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_branch.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsan <nsan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:22:55 by nsan              #+#    #+#             */
/*   Updated: 2025/02/11 19:22:55 by nsan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tokens	*args_redirection_list(t_ast *left_node, t_tokens *whole_list)
{
	t_tokens	*temp;

	if (args_list_len_alloc (whole_list, &(left_node->args)) && \
	redirect_list_len_alloc (whole_list, &(left_node->redirect)))
	{
		temp = parse_cmd (left_node, whole_list);
		return (temp);
	}
	return (NULL);
}
