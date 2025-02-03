# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/18 17:41:52 by aoo               #+#    #+#              #
#    Updated: 2025/02/03 17:32:12 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -g #-Wall -Wextra -Werror
HEADER = -I Libft
RM = rm -rf

LIBFT_DIR = ./Libft
LIBFT = $(LIBFT_DIR)/libft.a

SRCS = main.c utils_str.c utils_ast.c utils_extras.c utils_syntax_check.c built_ins.c \
		utils_token.c ast_args.c node_branch.c ast_redirection.c ast_branch.c ast_utils.c \
		utils.c redirection.c execution.c first_processing.c \
		built_in/export.c built_in/env.c built_in/unset.c built_in/pwd.c built_in/echo.c\
		built_in/cd.c signals.c

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
