# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aoo <aoo@student.42singapore.sg>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/18 17:41:52 by aoo               #+#    #+#              #
#    Updated: 2025/03/17 13:58:01 by aoo              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
HEADER = -I Libft
RM = rm -rf

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

SRCS = main.c execution.c first_processing.c second_processing.c free_all.c print_msg.c signals.c node_branch.c\
	\
	ast.c ast_syntax_check.c ast_args.c ast_redirection.c ast_branch.c ast_utils.c \
	\
	token_utils.c tokens.c redirection.c\
	\
	built_in/export.c built_in/env.c built_in/unset.c built_in/pwd.c built_in/echo.c built_in/cd.c built_in/exit.c \
	\
	utils_envp.c utils_export.c utils_core.c utils_exe_path.c utils_token2.c \
	utils_exe.c utils_heredoc.c utils_redirection.c utils_signal.c \

OBJS = ${SRCS:.c=.o}

all: ${NAME}
	@echo "${NAME} created."

${NAME}: ${OBJS} ${LIBFT}
	@echo "${NAME} compiling..."
	@${CC} ${CFLAGS} ${HEADER} -lft -L${LIBFT_DIR} ${OBJS} ${LIBFT} -lreadline -o ${NAME}

${LIBFT}:
	@make -C ${LIBFT_DIR}

%.o: %.c
	@${CC} ${CFLAGS} ${HEADER} -c $< -o $@

clean:
	@make clean -C ${LIBFT_DIR}
	@echo "mini_shell cleaning..."
	@${RM} ${OBJS}

fclean: clean
	@${RM} ${LIBFT}
	@${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
