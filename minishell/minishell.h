/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoo <aoo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 18:00:36 by aoo               #+#    #+#             */
/*   Updated: 2025/03/10 18:00:36 by aoo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <curses.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <term.h>
# include <time.h>

# define ERR_QUOTE "syntax error near unexpected token `"

extern volatile sig_atomic_t	g_sig_interrupt;

typedef enum e_token_types
{
	T_WORD = 0,
	T_PIPE = 1,
	T_REDIRECT_IN = 2,
	T_REDIRECT_OUT = 3,
	T_APPEND = 4,
	T_HERE_DOCS = 5,
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

typedef struct s_core
{
	struct s_ast	*ast;
	struct s_tokens	*tokens;
	struct s_list	*envp;
	char			*input;
	char			*history_path;
	pid_t			pid;
	int				status;
	int				single_time;
}	t_core;

typedef struct s_envp
{
	char	*key;
	char	*value;
}	t_envp;

// ast_args.c
int			args_list_len_alloc(t_tokens *whole_list, char ***args_list);

// ast_branch.c
t_tokens	*args_redirection_list(t_ast *left_node, t_tokens *whole_list);

// ast_redirections.c
int			redirect_list_len_alloc(t_tokens *whole_list, \
									char ***redirect_list);

// ast_syntax_check.c
int			syntax_word_error(t_tokens *temp);
int			syntax_pipe_error(t_tokens *temp);
int			syntax_redirect_error(t_tokens *temp);
int			check_grammar_syntax(t_tokens *head);

// ast_utils.c
void		print_ast(t_ast *ast_node);

// ast.c
int			init_ast(t_core *core);
void		create_ast(t_ast *ast_node, t_tokens *whole_list);

// execution.c
void		execute_ast(t_core *core);

// first_processing.c
char		*handle_env(char *str, t_core *core);
char		*handle_esc(char *str, char **result, int in_quote);
char		*handle_quotes(char *str);

// free_all.c
void		reset_close_fd(int *org_fd, int reset, int closee);
void		free_envp(void *data);
void		free_tokens(t_tokens **head);
void		free_ast(t_ast **ast);
void		free_core(t_core *core);

// main.c
int			get_input(t_core *core);
int			is_in_quote(char *str);
int			history_write(char *input, t_core *core);
void		print_err_msg(char *msg1, char *msg2, char *msg3);
int			init_token(t_core *core);

// node_branch.c
t_tokens	*parse_cmd(t_ast *left_node, t_tokens *whole_list);

// print_msg.c
int			print_heredoc_err(char *eof);
void		print_err_msg(char *msg1, char *msg2, char *msg3);

// redirection.c
int			redirection(char **redirect);

// signals.c
void		handle_sigint(int sigint);
void		handle_sigint_heredoc(int sigint);
void		set_signal_heredoc(void);
void		signal_pipe(int status, t_core *core);

// token_utils.c
t_tokens	*create_new_token(char *str);
void		append_token(t_tokens **head, t_tokens *new_node);
void		tokenize_str(t_tokens *head);

// tokens.c
void		create_add_token(t_tokens **head, char *str);
int			special_char_check(char curr_c, char next_c, char *str, \
t_tokens **head);
void		handle_space(char *input, t_tokens **head, char **start, int i);
void		handle_special_char(char *input, t_tokens **head, char **start, \
int *i);
t_tokens	*string_split(char *input);

// export.c
void		new_env(char *key, char *value, t_list **envp);
void		update_env(char *value, t_list *envp);
void		export_noargs(t_list *envp);
void		print_export(void *data);
int			export(char **args, t_list *envp, int status);

// utils_core.c
t_core		*init_core(char **envpath);
t_list		*init_envp(char **envpath);
t_list		*init_env_empty(t_list *envp);

// utils_envp.c
t_list		*find_env(char *key, t_list *envp);
char		*ft_getenv(char *key, t_list *envp);
void		get_keypair(char *arg, char *result[2]);

// utils_exe_path.c
void		update_udscore_env(t_ast *l_node, t_core *core);
int			get_p_path(char *cmd, char *envp_path, char **path);
char		**envp_toarray(t_list *envp);
int			envp_arrsize(t_list *envp);

// utils_exe.c
void		exec_cmd(char **args, t_core *core);
int			external(t_ast *l_node, int *org_fd, t_core *core);
int			execution_cmd(t_ast *l_node, t_core *core, int *org_fd);

// utils_export.c
t_list		*copy_envp(t_list *envp);
int			env_key_check(char *key, char *args);
void		sort_envp(t_list *envp);

// utils_heredoc.c
char		*get_heredoc(char *eof, int quote);
void		erase_quote(t_tokens *current);
void		prepare_heredoc(t_core *core);

// utils_redirection.c
int			re_input(char *file, int *in_fd);
int			re_output(char *file, int append);
int			re_heredoc(char *data, int *in_fd);
int			re_spec_in(char *file, int *in_fd);

// utils_signal.c
int			get_interrupt(t_core *core);
int			signal_status(int status);
int			signal_print(int status);
int			signal_pipe_exit(int status, t_core *core);

// built-in/env
int			env(t_list *envp);

// built-in/echo
int			echo_n(char **args);

// built-in/pwd
int			pwd(void);

// built-in/cd
int			cd(char **args, t_list *envp);

// built-in/unset
int			unset(char **args, t_list **envp);

// built-in/exit
int			ft_exit(char **args, int *org_fd, t_core *core);

// history
int			history_output(t_core *core);

#endif