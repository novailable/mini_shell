/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoo <aoo@student.42singapore.sg>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 04:56:28 by aoo               #+#    #+#             */
/*   Updated: 2025/02/03 05:17:04 by aoo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	cd(char **args, t_list *envp)
{
	if (args && args[2])
		return (write(2, "minishell: cd: too many arguments\n", 35), 1);
	else if (args[1] && chdir(args[1]) == -1)
		return (perror("minishell : "), 1);
	return (0);
		// return (printf("minishell: cd: %s No such file or directory\n", args[1]), 1);
}
