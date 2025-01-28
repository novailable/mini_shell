/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoo <aoo@student.42singapore.sg>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 13:32:19 by aoo               #+#    #+#             */
/*   Updated: 2025/01/28 10:36:04 by aoo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_export(void *data)
{
	t_envp	*env_var;

	env_var = (t_envp *)data;
	if (ft_strcmp(env_var->key, "_"))
	{
		printf("deaclare -x %s", env_var->key);
		if (env_var->value)
			printf("=\"%s\"", env_var->value);
		printf("\n");
	}
}

void	free_envp(void *data)
{
	t_envp	*env_var;

	env_var = (t_envp *)data;
	free(env_var->key);
	free(env_var->value);
	free(env_var);
}

int	envp_arrsize(t_list *envp)
{
	int	i;

	i = 0;
	while (envp)
	{
		if (((t_envp *)envp->data)->value != NULL)
			i++;
		envp = envp->next;
	}
	return (i);
}

char	**envp_toarray(t_list *envp)
{
	t_envp	*envp_var;
	char	**envp_array;
	int		i;

	i = 0;
	envp_array = (char **)malloc(sizeof(char *) * (envp_arrsize(envp) + 1));
	while (envp)
	{
		envp_var = (t_envp *)envp->data;
		if (envp_var->value != NULL)
		{
			envp_array[i] = ft_strjoin(envp_var->key, "=", 0, 0);
			envp_array[i] = ft_strjoin(envp_array[i], envp_var->value, 1, 0);
			i++;
		}
		envp = envp->next;
	}
	return (envp_array[i] = NULL, envp_array);
}

t_list	*copy_envp(t_list *envp)
{
	t_list	*result;
	t_envp	*env_var;

	result = NULL;
	while (envp)
	{
		env_var = (t_envp *)malloc(sizeof(t_envp));
		env_var->key = ft_strdup(((t_envp *)envp->data)->key);
		env_var->value = ft_strdup(((t_envp *)envp->data)->value);
		ft_lstadd_back(&result, ft_lstnew((void *)env_var));
		envp = envp->next;
	}
	return (result);
}

void	sort_envp(t_list *envp)
{
	int		swapped;
	void	*temp;
	t_list	*current;

	if (!envp)
		return ;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		current = envp;
		while (current && current->next)
		{
			if (ft_strcmp(((t_envp *)current->data)->key, \
			((t_envp *)current->next->data)->key) > 0)
			{
				temp = current->data;
				current->data = current->next->data;
				current->next->data = temp;
				swapped = 1;
			}
			current = current->next;
		}
	}
}

void	export_noargs(t_list *envp)
{
	t_list	*copy;

	copy = copy_envp(envp);
	sort_envp(copy);
	ft_lstiter(copy, print_export);
}

int	env_key_check(char *key)
{
	char	*temp;

	temp = key;
	if (temp && *temp && !ft_isdigit(*temp))
	{
		while (*temp && (ft_isalnum(*temp) || *temp == '_'))
		{
			temp++;
			if (*temp == '\0')
				return (0);
		}
	}
	return (printf("export : not a valid identifier : %s\n", key), 1);
}

char	*ft_strcjoin(char *str, char c)
{
	char	*result;
	int		char_len;
	int		i;

	char_len = 2;
	if (c == '\0')
		char_len = 1;
	result = malloc(sizeof(char) * (ft_strlen(str) + char_len));
	i = 0;
	while (str && str[i])
	{
		result[i] = str[i];
		i++;
	}
	if (c)
		result[i++] = c;
	result[i] = '\0';
	free(str);
	return (result);
}

char	*heredoc_processing(char *str)
{
	char	*result;
	int		in_quote;

	result = NULL;
	in_quote = 0;
	while (*str)
	{
		if (*str == '\\')
			str = handle_esc(str, &result, in_quote);
		else if (*str == '\'')
			str = handle_sq(str, &result);
		else if (*str++ == '\"')
		{
			while (*str && *str != '\"')
			{
				if (*str == '\\')
					str = handle_esc(str, &result, 1);
				else
					result = ft_strcjoin(result, *str++);
			}
			result = ft_strcjoin(result, '\0');
			str++;
		}
		else
			result = ft_strcjoin(result, *str++);
	}
	return (result);
}

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

void	ft_strsncpy(char **dest, char **src, int n)
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


