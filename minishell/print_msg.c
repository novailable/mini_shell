/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoo <aoo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 17:29:49 by nsan              #+#    #+#             */
/*   Updated: 2025/03/15 21:49:17 by aoo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_heredoc_err(char *eof)
{
	ft_putstr_fd("minishell: warning: here-document delimited by ",
		STDERR_FILENO);
	ft_putstr_fd("end-of-file (wanted `", STDERR_FILENO);
	ft_putstr_fd (eof, STDERR_FILENO);
	ft_putstr_fd ("')\n", STDERR_FILENO);
	return (1);
}

void	print_err_msg(char *msg1, char *msg2, char *msg3)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(msg1, 2);
	ft_putstr_fd(msg2, 2);
	ft_putstr_fd(msg3, 2);
}
