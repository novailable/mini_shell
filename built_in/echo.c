/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoo <aoo@student.42singapore.sg>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 21:18:39 by aoo               #+#    #+#             */
/*   Updated: 2025/02/11 13:57:14 by aoo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	echo_n(char **args, t_list *envp, int status)
{
	int 	n_line;

	n_line = ft_strcmp("-n", args[1]);
	if (n_line == 0)
		args++;
	while (*(++args))
	{
		printf("%s", *args);
		if (*(args + 1))
			printf(" ");
	}
	if (n_line != 0)
		printf("\n");
	return (status);
}
