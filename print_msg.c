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

void print_heredoc_err(char *eof)
{
    ft_putstr_fd("minishell: warning: here-document delimited by end-of-file (wanted `", STDERR_FILENO);
    ft_putstr_fd(eof, STDERR_FILENO);
    ft_putstr_fd("')\n", STDERR_FILENO);
}