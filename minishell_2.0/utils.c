/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: nsan <nsan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 13:32:19 by aoo               #+#    #+#             */
/*   Updated: 2025/03/03 17:37:21 by nsan             ###   ########.fr       */
=======
/*   By: aoo <aoo@student.42singapore.sg>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 13:32:19 by aoo               #+#    #+#             */
/*   Updated: 2025/03/02 16:04:17 by aoo              ###   ########.fr       */
>>>>>>> 4cdeb0f6219f9fcf8d9941a671c90a0876c7291f
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

<<<<<<< HEAD
void print_export(void *data)
{
	t_envp *env_var;
=======
void	print_export(void *data)
{
	t_envp	*env_var;
>>>>>>> 4cdeb0f6219f9fcf8d9941a671c90a0876c7291f

	env_var = (t_envp *)data;
	if (ft_strcmp(env_var->key, "_"))
	{
		printf("deaclare -x %s", env_var->key);
		if (env_var->value)
			printf("=\"%s\"", env_var->value);
		printf("\n");
	}
}

<<<<<<< HEAD
void free_envp(void *data)
{
	t_envp *env_var;
=======
void	free_envp(void *data)
{
	t_envp	*env_var;
>>>>>>> 4cdeb0f6219f9fcf8d9941a671c90a0876c7291f

	env_var = (t_envp *)data;
	free(env_var->key);
	free(env_var->value);
	free(env_var);
}

<<<<<<< HEAD
int envp_arrsize(t_list *envp)
{
	int i;
=======
int	envp_arrsize(t_list *envp)
{
	int	i;
>>>>>>> 4cdeb0f6219f9fcf8d9941a671c90a0876c7291f

	i = 0;
	while (envp)
	{
		if (((t_envp *)envp->data)->value != NULL)
			i++;
		envp = envp->next;
	}
	return (i);
}

<<<<<<< HEAD
char **envp_toarray(t_list *envp)
{
	t_envp *envp_var;
	char **envp_array;
	int i;
=======
char	**envp_toarray(t_list *envp)
{
	t_envp	*envp_var;
	char	**envp_array;
	int		i;
>>>>>>> 4cdeb0f6219f9fcf8d9941a671c90a0876c7291f

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

<<<<<<< HEAD
t_list *copy_envp(t_list *envp)
{
	t_list *result;
	t_envp *env_var;
=======
t_list	*copy_envp(t_list *envp)
{
	t_list	*result;
	t_envp	*env_var;
>>>>>>> 4cdeb0f6219f9fcf8d9941a671c90a0876c7291f

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

<<<<<<< HEAD
void sort_envp(t_list *envp)
{
	int swapped;
	void *temp;
	t_list *current;

	if (!envp)
		return;
=======
void	sort_envp(t_list *envp)
{
	int		swapped;
	void	*temp;
	t_list	*current;

	if (!envp)
		return ;
>>>>>>> 4cdeb0f6219f9fcf8d9941a671c90a0876c7291f
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		current = envp;
		while (current && current->next)
		{
<<<<<<< HEAD
			if (ft_strcmp(((t_envp *)current->data)->key,
						  ((t_envp *)current->next->data)->key) > 0)
=======
			if (ft_strcmp(((t_envp *)current->data)->key, \
			((t_envp *)current->next->data)->key) > 0)
>>>>>>> 4cdeb0f6219f9fcf8d9941a671c90a0876c7291f
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

<<<<<<< HEAD
void export_noargs(t_list *envp)
{
	t_list *copy;
=======
void	export_noargs(t_list *envp)
{
	t_list	*copy;
>>>>>>> 4cdeb0f6219f9fcf8d9941a671c90a0876c7291f

	copy = copy_envp(envp);
	sort_envp(copy);
	ft_lstiter(copy, print_export);
}

<<<<<<< HEAD
int env_key_check(char *key)
{
	char *temp;
=======
int	env_key_check(char *key)
{
	char	*temp;
>>>>>>> 4cdeb0f6219f9fcf8d9941a671c90a0876c7291f

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

<<<<<<< HEAD
char *ft_strcjoin(char *str, char c)
{
	char *result;
	int char_len;
	int i;
=======
char	*ft_strcjoin(char *str, char c)
{
	char	*result;
	int		char_len;
	int		i;
>>>>>>> 4cdeb0f6219f9fcf8d9941a671c90a0876c7291f

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
	if (str)
		free(str);
	return (result);
}

<<<<<<< HEAD
t_list *init_envp(char **envpath)
{
	t_list *envp;
	t_list *new;
	t_envp *env_var;
	char *value;
=======
t_list	*init_envp(char **envpath)
{
	t_list	*envp;
	t_envp	*env_var;
	char	*value;
>>>>>>> 4cdeb0f6219f9fcf8d9941a671c90a0876c7291f

	envp = NULL;
	while (*envpath)
	{
		env_var = malloc(sizeof(t_envp));
		if (!env_var)
			return (NULL);
<<<<<<< HEAD
		env_var->key = ft_strndup(*envpath,
								  ft_strchr(*envpath, '=') - *envpath);
=======
		env_var->key = ft_strndup(*envpath, \
						ft_strchr(*envpath, '=') - *envpath);
>>>>>>> 4cdeb0f6219f9fcf8d9941a671c90a0876c7291f
		value = ft_strchr(*envpath, '=') + 1;
		env_var->value = ft_strdup(value);
		ft_lstadd_back(&envp, ft_lstnew(env_var));
		envpath++;
	}
	return (envp);
}

<<<<<<< HEAD
void ft_strsncpy(char **dest, char **src, int n)
{
	int i;
=======
void	ft_strsncpy(char **dest, char **src, int n)
{
	int	i;
>>>>>>> 4cdeb0f6219f9fcf8d9941a671c90a0876c7291f

	i = 0;
	while (src[i] && i < n)
	{
		dest[i] = ft_strdup(src[i]);
		if (!dest[i])
			free_mem(dest, i);
		i++;
	}
}

<<<<<<< HEAD
int is_in_quote(char *str)
{
	int i;
	int in_quote;
=======
int	is_in_quote(char *str)
{
	int	i;
	int	in_quote;
>>>>>>> 4cdeb0f6219f9fcf8d9941a671c90a0876c7291f

	i = 0;
	in_quote = 0;
	while (str[i])
	{
<<<<<<< HEAD
=======
		if (str[i] == '\\' && str[i + 1] && in_quote != '\'')
		{
			i += 2;
			continue ;
		}
>>>>>>> 4cdeb0f6219f9fcf8d9941a671c90a0876c7291f
		is_quote("\'\"", str[i], &in_quote);
		i++;
	}
	return (in_quote);
}