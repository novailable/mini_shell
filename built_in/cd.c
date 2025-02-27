/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoo <aoo@student.42singapore.sg>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 04:56:28 by aoo               #+#    #+#             */
/*   Updated: 2025/02/13 17:11:51 by aoo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	cd(char **args, t_list *envp)
{
	char	*new_path;
	char	*old_path;
	char	*export_args[3];

	if (args && args[2])
		return (write(2, "minishell: cd: too many arguments\n", 35), 1);
	if (!args[1] || !ft_strcmp("~", args[1]))
		new_path = ft_getenv("HOME", envp);
	else
		new_path = args[1];
	if (chdir(new_path) == -1)
		return (perror("minishell"), 1);
	old_path = ft_strjoin("OLDPWD=", ft_getenv("PWD", envp), 0, 0);
	new_path = ft_strjoin("PWD=", getcwd(NULL, 0), 0, 1);
	export_args[0] = "export";
	export_args[1] = old_path;
	export_args[2] = NULL;
	export (export_args, envp, 0);
	free(old_path);
	export_args[1] = new_path;
	export (export_args, envp, 0);
	free(new_path);
	return (0);
}
