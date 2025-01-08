/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsan <nsan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 16:40:05 by nsan              #+#    #+#             */
/*   Updated: 2024/12/17 21:11:43 by nsan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <curses.h>
#include <term.h>
#include "libft/libft.h"

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
} t_token_types;

typedef struct s_tokens
{
	char *str;
	t_token_types tok_types;
	struct s_tokens *next;
} t_tokens;

typedef struct s_ast{
	t_token_types type;
	struct s_ast *left;
	struct s_ast *right;
	char **cmd;
	char *out_file;
	t_tokens *cmd_linked_list;
}t_ast;



void detect_str(char *str, t_tokens tokens);
t_tokens *create_new_token(char *str);
void	ft_lstadd_back(t_tokens **lst, t_tokens *new);
void tokenize_str(t_tokens *new_token, char *str);
t_tokens **tokenization(char **dest, int count);
t_ast *ast(t_tokens **whole_list);
t_ast *parse_cmd(t_ast *ast_node, t_tokens **whole_list, t_tokens *ref_ptr);
void parse_pipe(t_tokens **whole_list, t_ast *ast_node);
void parse_redirect(t_tokens **whole_list, t_ast *ast_node, int flag);
int check_grammar_syntax(t_tokens **whole_list);
void cd_built_in();
void ft_built_ins(char **list_of_cmd);
char *new_line_input(int flag, char *delimeter);
int quote_check(const char *input_str);
void handle_newline(char *buf, int sz);
t_tokens *cmd_list(t_tokens **cmd_list, t_tokens *ref_ptr);
void	ft_lstadd_from_back(t_tokens **cmd_list, t_tokens *node);
t_tokens	*ft_lstlast(t_tokens *node);

#endif