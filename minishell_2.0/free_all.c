/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsan <nsan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:49:13 by nsan              #+#    #+#             */
/*   Updated: 2025/03/03 19:15:33 by nsan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void free_envp_list(t_list *envp)
// {
//     t_list* current;
//     t_list* tmp;

//     current = envp;
//     while(current)
//     {
//         tmp = current->next;
//         free_envp(current->data);
//         free(current);
//         current = tmp;
//     }
    
// }

void ret_free_envp(char *str, t_list *envp, t_tokens *tokens)
{
    printf("%s", str);
    if(tokens)
        free_tokens(tokens);
    ft_lstclear(&envp, free_envp);
}

void free_tokens_ast(t_tokens *tokens, t_ast *ast_node)
{
    free_tokens(tokens);
	free_ast(ast_node);
	free(ast_node);
}