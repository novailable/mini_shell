/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoo <aoo@student.42singapore.sg>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 16:40:05 by nsan              #+#    #+#             */
/*   Updated: 2025/01/20 12:41:56 by aoo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "Libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <curses.h>
# include <term.h>
# include <time.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <dirent.h>
# include <fcntl.h>
# include <errno.h>

//enum for tokenization
typedef enum e_token_types
{
	T_WORD = 0, //ls -l
	T_PIPE = 1, // |
	T_REDIRECT_IN = 2, // <
	T_REDIRECT_OUT = 3, // >
	T_APPEND = 4, // >>
	T_HERE_DOCS = 5, //<<
	T_VAR = 6, //$
}	t_token_types;

typedef struct s_tokens
{
	char			*str;
	t_token_types	tok_types;
	struct s_tokens	*next;
}	t_tokens;

typedef struct s_ast{
	t_token_types type;
	struct s_ast *left;
	struct s_ast *right;
	char **cmd;
	char *out_file;
}t_ast;

//envp
typedef struct s_envp
{
	char			*key;
	char			*value;
}	t_envp;


t_tokens *create_new_token(char *str);
void tokenize_str(t_tokens *head);
t_ast *ast(t_ast *ast_node, t_tokens *whole_list);
int	check_grammar_syntax(t_tokens *head);
void ft_built_ins(char **list_of_cmd);
char *new_line_input(int flag, char *delimeter);
int quote_check(const char *input_str);
void handle_newline(char *buf, int sz);
t_ast *cmd_node_branch(t_tokens *current);
char **parse_cmd(char ***args_list, t_tokens **whole_list, int flag);
t_ast *redirection_list(t_ast *node, t_tokens **whole_list);
void redirect_list_len_alloc(t_tokens **whole_list, char ***redirect_list);
t_ast *args_list(t_ast *node, t_tokens **whole_list) ;
void args_list_len_alloc(t_tokens **whole_list, char ***args_list);
void history_output(char *input);
int history_write(char *input);
void	append_token(t_tokens **head, t_tokens *new_node);
// void cd_built_in();

//built_in
void	pwd();
void	env(t_list *envp);
void	export(char **args, t_list *envp);
t_list	*find_env(char *key, t_list *envp);
char	*ft_getenv(char *key, t_list *envp);
void	unset(char **args, t_list **envp);

//utils
void	print_env(void *data);
void	print_export (void *data);
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
void	ft_strsncpy(char **dest, char **src, int n);
t_list	*init_envp(char **envpath);

#endif