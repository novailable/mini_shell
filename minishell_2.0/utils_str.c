/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsan <nsan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 17:01:19 by nsan              #+#    #+#             */
/*   Updated: 2025/03/04 18:31:19 by nsan             ###   ########.fr       */
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


void	handle_newline(char *buf, int sz)
{
	int	i;

	i = -1;
	while (++i < sz)
	{
		if (buf[i] != '\n')
			write(1, &buf[i], 1);
		else
			write(1, "\n", 1);
	}
}