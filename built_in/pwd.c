/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoo <aoo@student.42singapore.sg>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 21:19:06 by aoo               #+#    #+#             */
/*   Updated: 2025/02/03 04:51:22 by aoo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pwd()
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	printf("in");
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}
