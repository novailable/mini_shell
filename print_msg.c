/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:59:23 by marvin            #+#    #+#             */
/*   Updated: 2025/03/05 14:59:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_heredoc_err(char *eof)
{
	ft_putstr_fd("minishell: warning: here-document delimited by ",
		STDERR_FILENO);
	ft_putstr_fd("end-of-file (wanted `", STDERR_FILENO);
	ft_putstr_fd (eof, STDERR_FILENO);
	ft_putstr_fd ("')\n", STDERR_FILENO);
}

void	print_export(void *data)
{
	t_envp	*env_var;

	env_var = (t_envp *)data;
	if (ft_strcmp(env_var->key, "_"))
	{
		printf("deaclare -x %s", env_var->key);
		if (env_var->value)
			printf("=\"%s\"", env_var->value);
		printf("\n");
	}
}
