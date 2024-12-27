/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoo <aoo@student.42singapore.sg>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 09:58:26 by aoo               #+#    #+#             */
/*   Updated: 2024/12/27 11:44:33 by aoo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//export VAR1="hello world" && echo $VAR1 && cd /tmp && pwd && mkdir test_dir && cd test_dir &&
//touch file1 file2 file3 && ls -l | grep file && echo "This is a test" > file1 && cat file1 >> 
//file2 && cat file2 | grep test && unset VAR1 && echo $VAR1 || echo "VAR1 unset" && env &&
// echo $? && (echo "Parentheses test" && echo "This works") && ls invalid_dir 2> error.log 
//&& cat error.log && rm -rf /tmp/test_dir && exit

#include "mini_shell.h"

t_list	*init_envp(char **envpath)
{
	t_list	*envp;
	t_envp	*env_var;
	char	*value;

	envp = NULL;
	while (*envpath)
	{
		env_var = malloc(sizeof(t_envp));
		if (!env_var)
			return (NULL);
		env_var->key = ft_strndup(*envpath, \
						ft_strchr(*envpath, '=') - *envpath);
		value = ft_strchr(*envpath, '=') + 1;
		env_var->value = ft_strdup(value);
		ft_lstadd_back(&envp, ft_lstnew(env_var));
		envpath++;
	}
	return (envp);
}

int	main(int argc, char **argv, char **envpath)
{
	char	*input_str;
	char	**input;
	t_list	*envp;

	(void)argc;
	(void)argv;
	
	int	i;
	
	i = 0;
	// envp = init_envp(envpath);
	while (1)
	{
		input_str = readline("mini_shell % ");
		// if (input_str)
		// {
		// 	add_history(input_str);
		// 	printf("%s\n", ft_strtok())
		// }
		
	}
}