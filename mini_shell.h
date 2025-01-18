#ifndef MINI_SHELL_H
#define MINI_SHELL_H

#include "Libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <dirent.h>
#include <fcntl.h>
# include <errno.h>

//built_in

typedef struct s_envp
{
	char			*key;
	char			*value;
}	t_envp;


//built_in
void	pwd();
void	env(t_list *envp);
int		export(char **args, t_list *envp);
t_list	*find_env(char *key, t_list *envp);
char	*ft_getenv(char *key, t_list *envp);
void	unset(char **args, t_list **envp);

//utils
void	print_env(void *data);
void	print_export(void *data);
void	free_envp(void *data);
char	**envp_toarray(t_list *envp);
t_list	*copy_envp(t_list *envp);
void	sort_envp(t_list *envp);
void	export_noargs(t_list *envp);
int		env_key_check(char *key);
char	*ft_strcjoin(char *str, char c);
char	*heredoc_processing(char *str);


//execute
int		exec_cmd(char **args, t_list *envp);

//shits
char	**ft_split_2(char *str, char *delimiters, char *ignchars);
int		is_quote(char *q_chars, char c, int *in_quote);
char	*first_processing(char *str, t_list *envp);
char	*handle_esc(char *str, char **result, int in_quote);
char	*handle_sq(char *str, char **result);

#endif