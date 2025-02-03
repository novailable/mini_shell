/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoo <aoo@student.42singapore.sg>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 21:18:39 by aoo               #+#    #+#             */
/*   Updated: 2025/02/03 09:03:06 by aoo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	echo_n(char **args, t_list *envp, int status)
{
	int 	n_line;
	char	*text;

	// if (args[1])
	// 	text = first_processing(args[1], envp);
	text = args[1];
	n_line = ft_strcmp("-n", text);
	// free(text);
	if (n_line == 0)
		args++;
	while (*(++args))
	{
		text = first_processing(*args, envp, status);
		printf("%s", text);
		if (n_line)
			printf("\n");
		free(text);
	}
	return (status);
}
