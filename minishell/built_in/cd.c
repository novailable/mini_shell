/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsan <nsan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 04:56:28 by aoo               #+#    #+#             */
/*   Updated: 2025/03/16 19:52:02 by nsan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*handle_new_path(char **args, t_list *envp)
{
	char	*new_path;

	if (!args[1])
		new_path = ft_getenv("HOME", envp);
	else if (*args[1] == '~')
	{
		new_path = ft_strjoin(getenv("HOME"), ft_strchr(args[1], '/'), 0, 0);
		free(args[1]);
		args[1] = new_path;
	}
	else
		new_path = args[1];
	if (!new_path)
		return (NULL);
	return (new_path);
}

void	update_env_pwds(char *o_pwd, t_core *core)
{
	char	*old_path;
	char	*new_path;
	char	*export_args[3];

	old_path = ft_strjoin("OLDPWD=", o_pwd, 0, 0);
	new_path = ft_strjoin("PWD=", getcwd(NULL, 0), 0, 1);
	export_args[0] = "export";
	export_args[1] = old_path;
	export_args[2] = NULL;
	export(export_args, core);
	free(old_path);
	export_args[1] = new_path;
	export(export_args, core);
	free(new_path);
}

int	cd(char **args, t_core *core)
{
	size_t	size;
	char	*new_path;
	char	*o_pwd;

	size = ft_strslen(args);
	if (size > 2)
		return (write(2, "minishell: cd: too many arguments\n", 35), 1);
	if (size > 1 && !*args[1])
		return (0);
	new_path = handle_new_path(args, core->envp);
	o_pwd = getcwd(NULL, 0);
	if (!new_path)
		return (free(o_pwd), \
				print_err_msg("cd: HOME not set\n", NULL, NULL), 1);
	if (chdir(new_path) == -1)
		return (free(o_pwd), \
				print_err_msg("'", new_path, "'"), perror(" "), 1);
	update_env_pwds(o_pwd, core);
	free(o_pwd);
	return (0);
}
