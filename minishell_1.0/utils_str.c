/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoo <aoo@student.42singapore.sg>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 17:01:19 by nsan              #+#    #+#             */
/*   Updated: 2025/01/20 10:28:43 by aoo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int quote_check(const char *input_str)
{
	int flag;
	int	i;

	flag = 0;
	i = 0;
	while (input_str[i])
	{
		if (input_str[i] == '\"')
			return (1);
		i++;
	}
	return (0);
}

// char *new_line_input(int flag, char *delimeter) //delimeter has "some word"
// {
// 	char *output;
// 	char *new_line;
// 	char *next_input;
// 	char *input = readline(">");
// 	if(flag == 0)
// 	{
// 		if (!quote_check(input))
// 		{
// 			new_line = ft_strjoin(input, "\n");
// 			free(input);
// 			input = new_line;
// 			next_input = new_line_input(0, NULL);
// 			output = ft_strjoin(input, next_input);
// 		}
// 		else
// 		{
// 			if(ft_strncmp(input, "\"", 1) == 0)
// 				input[0] = '\0';
// 			output = input;
// 		}
// 	}
// 	else if(flag == 1)
// 	{
// 		int word_len = ft_strlen(delimeter);
// 		if(ft_strncmp(input, delimeter, word_len))
// 		{
// 			new_line = ft_strjoin(input, "\n");
// 			free(input);
// 			input = new_line;
// 			next_input = new_line_input(1, delimeter);
// 			output = ft_strjoin(input, next_input);
// 		}
// 		else
// 		{
// 			if(ft_strncmp(input, delimeter, word_len) == 0)
// 				input[0] = '\0';
// 			output = input;
// 		}
// 	}
// 	return (output);
// }

void handle_newline(char *buf, int sz)
{
	int i;

	i = -1;
	while(++i < sz)
	{
		if(buf[i] != '\n')
			write(1, &buf[i], 1);
		else
			write(1, "\n", 1);
	}
}