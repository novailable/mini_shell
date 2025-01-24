/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_branch.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 10:29:48 by marvin            #+#    #+#             */
/*   Updated: 2025/01/23 10:29:48 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tokens    *args_redirection_list(t_ast *left_node, t_tokens *whole_list)
{
	args_list_len_alloc(whole_list, &(left_node->args));
	redirect_list_len_alloc(whole_list,  &(left_node->redirect));
    // if(!left_node->args)
    //     printf("left node is null\n");
    if (left_node->args == NULL)
        printf("left_node->args null\n");
    if (left_node->redirect == NULL)
        printf("left_node->redirect null\n");
    t_tokens *temp = parse_cmd(left_node, whole_list);
    return (printf("%s\n", left_node->args[0]), temp);
}