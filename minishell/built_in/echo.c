/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsan <nsan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 19:04:41 by nsan              #+#    #+#             */
/*   Updated: 2025/03/10 19:04:41 by nsan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_newline(char **args, int *n_line)
{
	int	i;
	int	j;

	i = 0;
	while (args[i] && ft_strncmp("-n", args[i], 2) == 0)
	{
		j = 1;
		while (args[i][j] == 'n')
			j++;
		if (args[i][j] != '\0')
		{
			if (i > 0)
			{
				*n_line = 0;
				break ;
			}
			*n_line = 1;
			break ;
		}
		*n_line = 0;
		i++;
	}
	return (i);
}

int	echo_n(char **args)
{
	int	n_line;
	int	i;

	n_line = 1;
	args++;
	i = is_newline(args, &n_line);
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (n_line)
		printf("\n");
	return (0);
}
