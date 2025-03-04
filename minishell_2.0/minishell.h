/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 16:40:05 by nsan              #+#    #+#             */
/*   Updated: 2025/02/13 16:41:13 by aoo              ###   ########.fr       */
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

# define PROMPT "\033[38;2;131;255;212mminishell % \001\033[0m\002"

extern int g_sig_interrupt;

//enum for tokenization
typedef enum e_token_types
{
	T_WORD = 0, //ls -l
	T_PIPE = 1, // |
	T_REDIRECT_IN = 2, // <
	T_REDIRECT_OUT = 3, // >
	T_APPEND = 4, // >>
	T_HERE_DOCS = 5, //<<
}	t_token_types;

typedef struct s_tokens
{
	char			*str;
	t_token_types	tok_types;
	struct s_tokens	*next;
}	t_tokens;

typedef struct s_ast
{
	struct s_ast	*left;
	struct s_ast	*right;
	char			**args;
	char			**redirect;
}	t_ast;

//envp
typedef struct s_envp
{
	char			*key;
	char			*value;
}	t_envp;

t_tokens	*string_split(char *input);
t_tokens *create_new_token(char *str);
void tokenize_str(t_tokens *head);
void 	ast(t_ast *ast_node, t_tokens *whole_list);
int	check_grammar_syntax(t_tokens *head, char *input);
void ft_built_ins(char **list_of_cmd);
// char *new_line_input(int flag, char *delimeter);
int quote_check(const char *input_str);
void handle_newline(char *buf, int sz);
// t_ast *cmd_node_branch(t_tokens *current);
t_tokens 	*parse_cmd(t_ast *left_node, t_tokens *whole_list);
t_ast *redirection_list(t_ast *node, t_tokens **whole_list);
void redirect_list_len_alloc(t_tokens *whole_list, char ***redirect_list);
t_ast *args_list(t_ast *node, t_tokens **whole_list) ;
void args_list_len_alloc(t_tokens *whole_list, char ***args_list);
int		history_output(void);
int		history_write(char *input);
void	append_token(t_tokens **head, t_tokens *new_node);
// void cd_built_in();
t_tokens	*args_redirection_list(t_ast *left_node, t_tokens *whole_list);


//utils_token
void	prepare_heredoc(t_tokens *head, t_list	*envp, int status);

//main
void	print_ast(t_ast *ast_node);
void	free_ast(t_ast *ast_node);

//built_in
int		pwd();
int		cd(char **args, t_list *envp);
int		env(t_list *envp);
int		export(char **args, t_list *envp, int status);
t_list	*find_env(char *key, t_list *envp);
char	*ft_getenv(char *key, t_list *envp);
int		unset(char **args, t_list **envp);
int		echo_n(char **args, t_list *envp, int status);


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
int		is_in_quote(char *str);

//execute
int		exec_cmd(char **args, t_list *envp);
char	*get_p_path(char *cmd, char *envp_path);
int		execute_ast(t_ast *ast_node, t_list *envp, int status);

// redirection
int		redirection(char **redirect);
char	*get_heredoc(char *eof, t_list *envp, int status);

//shits
char	**ft_split_2(char *str, char *delimiters, char *ignchars);
int		is_quote(char *q_chars, char c, int *in_quote);
// char	*first_processing(char *str, t_list *envp, int status);
void	ft_strsncpy(char **dest, char **src, int n);
t_list	*init_envp(char **envpath);

char	*handle_env(char *str, t_list *envp, int status);
char	*handle_quotes(char *str);

//signals
void	signal_handling();
// void control_c(int sigint);
void handle_signals();
void handle_sigint(int sigint);
void handle_sigint_process(int sigint);
void handle_sigquit_process(int sigint);
void handle_sigint_heredoc(int sigint);

void	set_signal(void);
void	set_signal_heredoc(void);
void	stop_signal(void);
void	default_signal(void);
int		wait_signal_status(int status);


//helpers
int is_balanced_quotes(char *input);
void create_add_token(t_tokens **head, char *str);
int special_char_check(char curr_c, char next_c, char *str, t_tokens **head);

//others
// int apply_redirections(t_ast *node);

//free
void free_envp_list(t_list *envp);
void ret_free_envp(char* str, t_list *envp, t_tokens *tokens);
void	free_tokens(t_tokens *head);
void free_tokens_ast(t_tokens *tokens, t_ast *ast_node);

#endif