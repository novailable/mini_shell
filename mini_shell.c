/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoo <aoo@student.42singapore.sg>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 09:58:26 by aoo               #+#    #+#             */
/*   Updated: 2024/12/21 18:36:26 by aoo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//export VAR1="hello world" && echo $VAR1 && cd /tmp && pwd && mkdir test_dir && cd test_dir && touch file1 file2 file3 && ls -l | grep file && echo "This is a test" > file1 && cat file1 >> file2 && cat file2 | grep test && unset VAR1 && echo $VAR1 || echo "VAR1 unset" && env && echo $? && (echo "Parentheses test" && echo "This works") && ls invalid_dir 2> error.log && cat error.log && rm -rf /tmp/test_dir && exit


#include "mini_shell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*input_str;
	char	**input;

	(void)argc;
	(void)argv;
	
	int	i;
	
	i = 0;
	while (*envp)
		printf("%s\n", *envp++);
	// while (1)
	// {
	// 	input_str = readline("mini_shell % ");
	// 	if (input_str)
	// 	{
	// 		add_history(input_str);
	// 		input = ft_split_2(input_str, " \t", "\'\"");
	// 	}
		
	// }
}