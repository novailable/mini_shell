/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoo <aoo@student.42singapore.sg>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 09:58:26 by aoo               #+#    #+#             */
/*   Updated: 2025/01/20 11:59:18 by aoo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//export VAR1="hello world" && echo $VAR1 && cd /tmp && pwd && mkdir test_dir && cd test_dir &&
//touch file1 file2 file3 && ls -l | grep file && echo "This is a test" > file1 && cat file1 >> 
//file2 && cat file2 | grep test && unset VAR1 && echo $VAR1 || echo "VAR1 unset" && env &&
// echo $? && (echo "Parentheses test" && echo "This works") && ls invalid_dir 2> error.log 
//&& cat error.log && rm -rf /tmp/test_dir && exit

#include "mini_shell.h"

__pid_t ft_getpid()
{
	__pid_t pid;

	pid = fork();
	if (pid == -1)
		return (perror("fork failed"), -1);
	if (pid == 0)
		exit(0);
	else
		return (wait(NULL), pid);
}

// char	*first_processing(char *str, t_list *envp)
// {
// 	char	*result;
// 	int		i;
// 	int		in_quote;
// 	char	*start;
// 	i = 0;
// 	in_quote = 0;
// 	result = NULL;
// 	while (str && str[i])
// 	{
// 		if (str[i] == '\\' && !in_quote)
// 		{
// 			if (str[i] == '\\' || str[i] == '\'' \
// 			|| str[i] == '$' || str[i] == '\"')
// 			{
// 				result = ft_strcjoin(result, str[++i]);
// 				i++;
// 			}
// 			else if (str[i + 1] == '\n')
// 				i += 2;
// 			else
// 				result = ft_strcjoin(result, str[++i]);
// 		}
// 		else if (str[i] == '$')
// 		{
// 			start = ++i + str;
// 			while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
// 				i++;
// 			start = ft_strndup(start, (str + i) - start);
// 			if (start && *start)
// 			{
// 				result = ft_strjoin(result, ft_getenv(start, envp), 1, 0);
// 				free(start);
// 			}
// 			else
// 				result = ft_strcjoin(result, str[i - 1]);
// 		}
// 		else if (str[i] == '\'')
// 		{
// 			i++;
// 			while (str[i])
// 			{
// 				if (str[i] == '\'')
// 				{
// 					result = ft_strcjoin(result, '\0');
// 					i++;
// 					break;
// 				}
// 				else
// 					result = ft_strcjoin(result, str[i++]);
// 			}
// 		}
// 		else if (str[i] == '\"')
// 		{
// 			in_quote = str[i++];
// 			while (str[i] && in_quote)
// 			{
// 				if (str[i] == '\\')
// 				{
// 					if (str[i + 1] == '\\' || \
// 					str[i + 1] == '$' || str[i + 1] == '\"')
// 					{
// 						result = ft_strcjoin(result, str[++i]);
// 						i++;
// 					}
// 					else if (str[i + 1] == '\n')
// 						i += 2;
// 					else
// 						result = ft_strcjoin(result, str[i++]);
// 				}
// 				else if (str[i] == '$')
// 				{
// 					start = ++i + str;
// 					while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
// 						i++;
// 					start = ft_strndup(start, (str + i) - start);
// 					if (start && *start)
// 					{
// 						result = ft_strjoin(result, ft_getenv(start, envp), 1, 0);
// 						free(start);
// 					}
// 					else
// 						result = ft_strcjoin(result, str[i - 1]);
// 				}
// 				else if (str[i] == in_quote)
// 				{
// 					in_quote = 0;
// 					result = ft_strcjoin(result, '\0');
// 					i++;
// 				}
// 				else
// 					result = ft_strcjoin(result, str[i++]);
// 				// if (str[i] == in_quote)
// 				// {
// 				// 	in_quote = 0;
// 				// 	i++;
// 				// }
// 			}
// 		}
// 		else
// 			result = ft_strcjoin(result, str[i++]);
// 	}
// 	return (result);
// }

int	is_end_quote(char *str)
{
	int	i;
	int	in_quote;

	i = 0;
	in_quote = 0;
	while (str[i])
	{
		if (str[i] == '\\' && str[i + 1] && in_quote != '\'')
		{
			i += 2;
			continue;
		}
		is_quote("\'\"", str[i], &in_quote);
		i++;
	}
	return (in_quote);
}

void	sprint_env(char **envp)
{
	char	**temp_env;
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (envp[i])
		i++;
	temp_env = (char **)malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (envp[++i])
		temp_env[i] = envp[i];
	temp_env[i] = NULL;
	i = -1;
	while (temp_env[++i])
	{
		j = i + 1;
		while (temp_env[j])
		{
			if (ft_strcmp(temp_env[i], temp_env[j]) > 0)
			{
				temp = temp_env[i];
				temp_env[i] = temp_env[j];
				temp_env[j] = temp;
			}
			j++;
		}
	}
	i = -1;
	while (temp_env[++i])
		if (*(temp_env[i]) != '_')
			printf("declare -x %s\n", temp_env[i]);
	free(temp_env);
}

int	main(int argc, char **argv, char **envpath)
{
	char	*input_str;
	char	**args;
	char	**envp_arr;
	// char	*input[] = {"TEST=\"Hello\\\"\\$TEST$PWD\\\"\"", "A=a", NULL};
	t_list	*envp;
	t_list	*copy;
	pid_t	pid;
	(void)argc;
	(void)argv;
	int	status;
	int	i;
	
	envp = init_envp(envpath);
	if (!envp)
		return (1);
	while (1)
	{
		input_str = readline("mini_shell % ");
		add_history(input_str);
		printf("%d\n", is_end_quote(input_str));
		char *f_p = first_processing(input_str, envp);
		char *h_p = heredoc_processing(input_str);
		printf("f_p %s, h_p %s\n", f_p, h_p);
		free(h_p);
		free(input_str);
		// printf("%d\n", is_end_quote(input_str));
		
		// args = ft_split(input_str, " ");
		
		// else if (!ft_strcmp(*args, "export"))
		// 	export(args, envp);
		// else if (!ft_strcmp(*args, "unset"))
		// 	unset(args, &envp);
		// else if (!ft_strcmp(*args, "pwd"))
		// 	pwd();
		// else
		// {
		// 	envp_arr = envp_toarray(envp);
		// 	for (int i = 0; envp_arr[i]; i++)
		// 		printf("%s\n", envp_arr[i]);
		// }
		// 	pid = fork();
		// 	if (pid == -1)
		// 		return (perror("fork failed"), 1);
		// 	if (pid == 0)
		// 	{
		// 		if (exec_cmd(args, envp) == -1)
		// 		{
		// 			perror("command not found ");
		// 			if (errno == EACCES)
		// 				exit (126);
		// 			exit (127);
		// 		}
		// 		exit (0);
		// 	}
		// 	else
		// 		waitpid(pid, &status, 0);
	}
	ft_lstclear(&envp, free_envp);
}