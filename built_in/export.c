/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoo <aoo@student.42singapore.sg>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 21:18:45 by aoo               #+#    #+#             */
/*   Updated: 2024/12/21 21:25:46 by aoo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	new_env(char *key_pair, char ***envp)
{
	int		i;
	char	**new_envp;

	i = 0;
	while ((*envp)[i])
		i++;
	printf("i : %d\n", i);
	new_envp = (char **)malloc(sizeof(char *) * (i + 2));
	if (!new_envp)
		return;
	i = 0;
	while ((*envp)[i])
	{
		new_envp[i] = strdup((*envp)[i]);
		i++;
	}
	new_envp[i] = strdup(key_pair);
	new_envp[i + 1] = NULL;
	*envp = new_envp;
}

void	update_env(char *key_pair, char *value, char ***envp)
{
	
}

void	export(char **args, char **envp)
{
	int	i;


	i = 0;
	if (!args)
		while (envp[i])
			printf("declare -x %s\n", envp[i++]);
	else
	{
		while (args[i])
		{
			
		}
	}

}

int	main(int argv, char **argc, char **envp)
{
	new_env("A=hi", &envp);
	env(envp); 
	printf("getenv : %s\n", getenv("A"));
}