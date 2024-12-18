/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 20:54:08 by nsan              #+#    #+#             */
/*   Updated: 2024/12/18 11:29:19 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void tokenization(char **dest, int count)
{
	t_tokens *new_token;
	t_tokens **whole_list = malloc(sizeof(t_tokens *) * count);
	int i;

	i = 0;
	*whole_list = NULL;
	while (dest[i] != NULL)
	{
		new_token = create_new_token(dest[i]);
		tokenize_str(new_token, dest[i]);
		ft_lstadd_back(whole_list, new_token);
		i++;
	}
	/*print out the whole list ["ls", "-l"] and its details*/
	// t_tokens *current = *whole_list;
	// int j = 0;
	// while (current != NULL)
	// {
	// 		printf("Content %d:\n", j);
	// 		printf("String: %s\n", current->str);
	// 		printf("Token: %u\n\n", current->tok_types);
	// 		current = current->next;
	// 		j++;
	// }
}