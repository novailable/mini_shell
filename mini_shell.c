/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoo <aoo@student.42singapore.sg>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 09:58:26 by aoo               #+#    #+#             */
/*   Updated: 2025/01/01 12:10:06 by aoo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//export VAR1="hello world" && echo $VAR1 && cd /tmp && pwd && mkdir test_dir && cd test_dir &&
//touch file1 file2 file3 && ls -l | grep file && echo "This is a test" > file1 && cat file1 >> 
//file2 && cat file2 | grep test && unset VAR1 && echo $VAR1 || echo "VAR1 unset" && env &&
// echo $? && (echo "Parentheses test" && echo "This works") && ls invalid_dir 2> error.log 
//&& cat error.log && rm -rf /tmp/test_dir && exit

#include "mini_shell.h"

t_list	*init_envp_lst(char **envpath)
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

void	*ft_strsncpy(char **dest, char **src, int n)
{
	int	i;

	i = 0;
	while (src[i] && i < n)
	{
		dest[i] = ft_strdup(src[i]);
		if (!dest[i])
			free_mem(dest, i);
		i++;
	}
}

char	**init_env(char **envpath)
{
	int		i;
	char	**n_envp;

	i = 0;
	while (envpath[i])
		i++;
	n_envp = malloc(sizeof(char *) * (i + 1));
	if (!n_envp)
		return (NULL);
	ft_strsncpy(n_envp, envpath, i);
	n_envp[i] = NULL;
	return (n_envp);
}

char	*ft_strcjoin(char *str, char c)
{
	char	*result;
	int		i;

	result = malloc(sizeof(char) * (ft_strlen(str) + 2));
	i = 0;
	while (str && str[i])
	{
		result[i] = str[i];
		i++;
	}
	result[i++] = c;
	result[i] = '\0';
	free(str);
	return (result);
}


// char	*first_processing(char *str, char **envp)
// {
// 	char	*result;
// 	int		start;
// 	int		i;
// 	int		j;

// 	result = NULL;
// 	// ft_bzero(result, ft_strlen(str));
// 	i = 0;
// 	j = 0;
// 	while (str[i] && str)
// 	{
// 		 if (str[i] == '\\' && !in_quote && \
//		(str[i + 1] == '\\' || str[i + 1] == '\'' \
//		|| str[i + 1] == '$' || str[i + 1] == '\"'))
// 		{
// 			// printf("%c, %c\n", result[j], str[i]);
// 			// result[j++] = str[++i];
// 			// i++;
// 			result = ft_strcjoin(result, str[++i]);
// 			i++;
// 		}
// 		else if (str[i] == '$')
// 		{
// 			start = ++i;
// 			while (str[i] && !ft_strchr("$\0", str[i]))
// 				i++;
// 			// result = ft_strjoin(result, ft_getenv(ft_str, envp))
// 		}
// 		else
// 		{
// 			result = ft_strcjoin(result, str[i++]);
// 			printf("re : %s\n", result);
// 		}
// 	}
// 	return (result);
// }


char	*first_processing(char *str, char **envp)
{
	char	*result;
	int		i;
	int		in_quote;
	char	*start;

	i = 0;
	in_quote = 0;
	result = NULL;
	while (str[i])
	{
		if (str[i] == '\\' && !in_quote)
		{
			if (str[i + 1] == '\\' || str[i + 1] == '\'' \
			|| str[i + 1] == '$' || str[i + 1] == '\"')
			{
				result = ft_strcjoin(result, str[++i]);
				i++;
			}
			else if (str[i + 1] == '\n')
				i += 2;
			else
				result = ft_strcjoin(result, str[i++]);
		}
		else if (str[i] == '$')
		{
			start = ++i + str;
			while (str[i] && !ft_strchr("\\\"$", str[i]))
				i++;
			start = ft_strndup(start, (str + i) - start);printf("start : %s\n", start);
			if (start && *start)
			{
				
				result = ft_strjoin(result, ft_getenv(start, envp), 1, 0);
				free(start);
			}
			else
				result = ft_strcjoin(result, str[i - 1]);
		}
		else if (str[i] == '\'')
        {
			i++;
            while (str[i] && str[i] != '\'')
                result = ft_strcjoin(result, str[i++]);
			i++;
        }
		else if (str[i] == '\"')
		{
			in_quote = str[i++];
			while (str[i] && in_quote)
			{
				if (str[i] == '\\')
				{
					if (str[i + 1] == '\\' || \
					str[i + 1] == '$' || str[i + 1] == '\"')
					{
						result = ft_strcjoin(result, str[++i]);
						i++;
					}
					else if (str[i + 1] == '\n')
						i += 2;
					else
						result = ft_strcjoin(result, str[i++]);
				}
				else if (str[i] == '$')
				{
					start = ++i + str;
					while (str[i] && !ft_strchr("\\\"$", str[i]))
						i++;
					start = ft_strndup(start, (str + i) - start);printf("start : %s\n", start);
					if (start && *start)
					{
						
						result = ft_strjoin(result, ft_getenv(start, envp), 1, 0);
						free(start);
					}
					else
						result = ft_strcjoin(result, str[i - 1]);
				}
				else
					result = ft_strcjoin(result, str[i++]);
				if (str[i] == in_quote)
				{
					in_quote = 0;
					i++;
				}
			}
		}
		else
            result = ft_strcjoin(result, str[i++]);
	}
	return (result);
}

char	*replace_env(char *str, char **envp)
{
	char	*result;
	char	*copy;
	int		i;

	i = 0;
	if (!str)
		return (NULL);
	
	// if (*str == '\'')
	// 	return (ft_strtrim(str, "\'"));
	// if (*str == '\"')
	// 	copy = ft_strndup(++str, ft_strlen(str) - 2);
	// else
	// 	copy = ft_strdup(str);

	// printf("copy : %s, len : %ld\n", copy, ft_strlen(str) - 2);
	result = first_processing(str, envp);
	// free(copy);
	// copy = result;
	// while (copy[i])
	// {
	// 	if (copy[i] == '$')
	// 		if (copy[i - 1] == '\\')
			
	// }
	printf("Result : %s\n", result);
	
		
}


int	main(int argc, char **argv, char **envpath)
{
	char	*input_str;
	// char	*input[] = {"\"Hello\"\$TEST$PWD\\\"\"", "A=a", NULL};
	// t_list	*envp;
	char	*save;
	char	**envp;
	(void)argc;
	(void)argv;
	
	int	i;
	
	i = 0;
	// env(ennvpath);
	envp = init_env(envpath);
	if (!envp)
		return (1);
	while (1)
	{
		input_str = readline("mini_shell % ");
		printf("input : %s\n", input_str);
		
		if (input_str)
		{
			add_history(input_str);
			replace_env(input_str, envp);		
		}
	}
	i = 0;
	while (envp[i])
		free(envp[i++]);
	free(envp);
}